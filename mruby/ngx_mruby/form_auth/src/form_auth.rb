
def log(s)
  Nginx.errlogger Nginx::LOG_ERR, "mruby>  [#{s}]"
end

def load_user_list(file)
  users = {}
  IO.open(IO.sysopen((file))) do |io|
    io.each do |line|
      params = line.chomp.split("\t")
      users[params[0]] = params[1] if 1 < params.size
    end
  end
  users
end

class QueryString
  def self.parse(query_string)
    qs = {}
    return qs  if query_string.nil?
    query_string.split('&').each do |item|
      params = item.split("=")
      next  if params.size == 0 || params[0].empty?
      qs[params[0]] = params[1]
    end
    qs
  end
end

class Cookie
  def self.parse(cookie)
    c = {}
    return c  if cookie.nil?
    cookie.split(/;\s*/).each do |item|
      params = item.split("=")
      next  if params.size == 0 || params[0].empty?
      c[params[0]] = params[1]
    end
    c
  end
end

def print_login_page(req_uri)
  Nginx.echo <<__HTML__
<!DOCTYPE html>
<html>
<head>
<title>Login</title>
<style>
form {
    width: 270px;
}
form > input, button {
    display: block;
    width: 100%;
}
form input[type="text"],
form input[type="password"] {
    padding: 0 8px;
    height: 44px;
    -moz-box-sizing: border-box;
    -webkit-box-sizing: border-box;
    box-sizing: border-box;
}
form input[type="password"] {
    margin-top: -1px;
    margin-bottom: 10px;
}
form button[type="submit"] {
    background-color: #5580af;
    color: #fff;
    border: 0;
    padding: 0 8px;
    height: 44px;
}
</style>
</head>
<body>
<h1>Login page</h1>
<form method="post" action="#{req_uri}">
    <input type="text" name="id" placeholder="id"></input>
    <input type="password" name="password" placeholder="password"></input>
    <button type="submit">Login</button>
</form>
</body>
</html>
__HTML__
end

req = Nginx::Request.new
cookie = Cookie::parse(req.headers_in['Cookie'])
log "cookie: #{req.headers_in['Cookie']}"

if cookie["login"] == "OK"
  log "already login"
  Nginx.redirect req.uri.nil? ? "/" : req.uri, Nginx::HTTP_MOVED_PERMANENTLY
elsif req.method == "POST"
  users = load_user_list(req.var.user_list)
  post = QueryString::parse(req.body)
  id = post['id']
  password = post['password']

  log "POST #{req.body}"
  log "id #{post['id']}"
  log "password #{post['password']}"

  if cookie["login"] == "OK"
    Nginx.return Nginx::DECLINED
  else
    if users.key?(id) && users[id] == password
      log "Login OK!!"
      req.headers_out['Set-Cookie'] = "login=OK"
      Nginx.return Nginx::DECLINED
    else
      Nginx.echo "NG!!"
    end
  end
else
  print_login_page req.uri
end

