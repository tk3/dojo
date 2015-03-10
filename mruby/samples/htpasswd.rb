class Htpasswd
  attr_accessor :users

  def initialize(filename)
    @filename = filename

    @users = {}
    IO.open(IO.sysopen((filename))) do |io|
      io.each do |line|
        user = Htpasswd.parse(line.chomp)
        @users[user[:username]] = user[:password]  unless user.nil?
      end
    end
  end

  def authn(username, passowrd)
    return false  unless @users.key?(username)
  end

  def self.parse(s)
    return nil  if s.nil? || s.empty? || s[0] == '#'
    params = s.split(":", 3)
    return nil  if params.length < 2

    {:username => params[0], :password => params[1]}
  end
end

h = Htpasswd.new("users")

puts h.users

