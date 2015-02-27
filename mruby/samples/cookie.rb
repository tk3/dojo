
class Cookie
  def self.parse(cookie)
    c = {}
    cookie.split(/;\s*/).each do |item|
      params = item.split("=")
      next  if params.size == 0 || params[0].empty?
      c[params[0]] = params[1]
    end
    c
  end
end

data = [
  '',
  'name',
  'name=',
  '=val',
  '=',
  'name=value',
  'name=value;',
  'name01=value01;name02',
  'name01=value01;=value02',
  'name01=value01;=value02',
  'name01=value01;=;=;',
  'name01=value01;;',
]

data.each {|d|
  c = Cookie.parse(d)
  #puts d
}

