def parse(s)
  return nil  if s.nil? || s.empty? || s[0] == '#'
  params = s.split(":", 3)
  return nil  if params.length < 2

  {:username => params[0], :password => params[1]}
end

data = [
  nil,
  "",
  "# comment",
  "::",
  ":::",
  "user1",
  "user1:",
  ":pass1",
  "::comment1",
  "user1:pass1",
  "user1:pass1:",
  "user1:pass1:comment1",
]

data.each do |d|
  u = parse d
  puts ">> #{d}"
  if u.nil?
    puts "  nil"
  else
    puts "  username=[#{u[:username]}], password=[#{u[:password]}]"
  end
  puts ""
end

