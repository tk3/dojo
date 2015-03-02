
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

data = [
  nil,
  '',
  'name',
  'name=',
  '=val',
  '=',
  'name=value',
  'name=value&',
  'name01=value01&name02',
  'name01=value01&=value02',
  'name01=value01&=value02',
  'name01=value01&=&=&',
  'name01=value01&&',
]

data.each {|d|
  puts QueryString.parse(d)
  #puts d
}

