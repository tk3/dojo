def basic_auth
  r = Nginx::Request.new
  realm = r.var.realm

  if r.headers_in["Authorization"].nil?
    r.headers_out["WWW-Authenticate"] = %Q(Basic realm="#{realm}")
    return Nginx::HTTP_UNAUTHORIZED
  end

  auth = r.headers_in["Authorization"]
  params = Base64::decode(auth.split(" ")[1]).split(":")

  unless yield(params[0], params[1])
    r.headers_out["WWW-Authenticate"] = %Q(Basic realm="#{realm}")
    return Nginx::HTTP_UNAUTHORIZED
  end

  return Nginx::DECLINED
end

def load_user_list(file)
  users = {}
  IO.open(IO.sysopen((file))) {|io|
    io.each {|line|
      params = line.chomp.split("\t")
      users[params[0]] = params[1] if 1 < params.size
    }
  }
  users
end

r = Nginx::Request.new
users = load_user_list(r.var.user_list)

Nginx.return basic_auth {|id, password|
  users.key?(id) && users[id] == password
}
