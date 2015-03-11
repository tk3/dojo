SERVER_NAME = "Trusterd"
SERVER_VERSION = "0.0.1"
SERVER_DESCRIPTION = "#{SERVER_NAME}/#{SERVER_VERSION}"

root_dir = "/home/vagrant/trusterd"

s = HTTP2::Server.new({
  :port           => 8080,
  :document_root  => "#{root_dir}/htdocs",
  :server_name    => SERVER_DESCRIPTION,

  :worker         => "auto",

  :key            => "#{root_dir}/ssl/server.key",
  :crt            => "#{root_dir}/ssl/server.crt",
  #:dh_params_file => "#{root_dir}/ssl/dh.pem",
  :tls => true,
  :callback => true,
})

module HTTP2
  class Server
    class BasicAuth
      def initialize(config)
        @config = {
          :realm_name => "Private page",
        }.merge(config)
        raise ArgumentError  unless @config.key?(:htpasswd)

        @users = {}
        IO.open(IO.sysopen(@config[:htpasswd])) do |io|
          io.each do |line|
            params = line.chomp.split("\t")
            @users[params[0]] = params[1]  if 1 < params.size
          end
        end
      end

      def authn(s)
        if s.r.headers_in["authorization"].nil?
          s.r.headers_out["www-authenticate"] = %Q(Basic realm="#{@config[:realm_name]}")
          s.set_status 401
          return false
        else
          auth = s.r.headers_in["authorization"]
          params = auth.split(" ")[1].unpack("m")[0].split(":")
          unless @users.key?(params[0]) && @users[params[0]] == params[1]
            s.r.headers_out["www-authenticate"] = %Q(Basic realm="#{@config[:realm_name]}")
            s.set_status 401
            return false
          end
          return true
        end
      end
    end
  end
end

basic = HTTP2::Server::BasicAuth.new({
  :realm_name  => "Private Area",
  :htpasswd    => "/home/vagrant/trusterd/user.list",
})

s.set_access_checker_cb {
  basic.authn(s)
}

# s.set_map_to_strage_cb {
#
#   p "callback bloack at set_map_to_strage_cb"
#   p s.filename            #=> /path/to/index.html
#   p s.uri                 #=> /index.html
#   p s.unparsed_uri        #=> /index.html?a=1&b=2
#   p s.percent_encode_uri  #=> /index.html?id=%E3%83%9F%E3
#   p s.args                #=> ?a=1&b=2
#   p s.body                #=> "post data"
#   p s.method              #=> "GET"
#   p s.scheme              #=> "https"
#   p s.authority           #=> "matsumoto-r.jp"
#   p s.host                #=> "matsumoto-r.jp"
#   p s.hostname            #=> "matsumoto-r.jp"
#   p s.client_ip           #=> "192.168.12.5"
#   p s.document_root       #=> "/path/to/htdocs"
#   p s.user_agent          #=> "trusterd_client"
#
#   p "if :server_status is true, use server status method"
#   p "the number of total requesting stream #{s.total_stream_request}"
#   p "the number of total requesting session #{s.total_session_request}"
#   p "the number of current connected sessions #{s.connected_sessions}"
#   p "the number of current processing streams #{s.active_stream}"
#
#   # location setting
#   if s.request.uri == "/index.html"
#     s.request.filename = "#{root_dir}/htdocs/hoge"
#   end
#   p s.request.filename
#
#   # you can use regexp if you link regexp mrbgem.
#   # Or, you can use KVS like mruby-redis or mruby-
#   # vedis and so on.
#
#   # reverse proxy config
#   # reciev front end with HTTP/2 and proxy upstream server with HTTP/1.x
#   # TODO: don't support connection with TLS to upstream server
#   # need :upstream => true
#
#   if s.request.uri =~ /^/$/
#     # upstream request uri default: /
#     s.upstream_uri = s.percent_encode_uri
#     s.upstream_host = "127.0.0.1"
#
#     # upstream port default: 80
#     #s.upstream_port = 8080
#
#     # upstream connection timeout default: 600 sec
#     #s.upstream_timeout = 100
#
#     # use keepalive deault: true
#     #s.upstream_keepalive = false
#
#     # use HTTP/1.0 protocol default: HTTP/1.1
#     #s.upstream_proto_major = 1
#     #s.upstream_proto_minor = 0
#   end
#
#   # dynamic content with mruby
#   if s.request.filename =~ /^.*\.rb$/
#     s.enable_mruby
#   end
#
#   # dynamic content with mruby sharing mrb_state
#   if s.request.filename =~ /^.*\_shared.rb$/
#     s.enable_shared_mruby
#   end
#
#   if s.request.uri =~ /hellocb/
#     s.set_content_cb {
#       s.rputs "hello trusterd world from cb"
#       s.echo "+ hello trusterd world from cb with \n"
#     }
#   end
# }

# create response just before send response
# s.set_fixups_cb {
#  # update server header
#  s.r.response_headers["server"] = "other server"
#}

# #If define set_content_cb this scope, callback only once
# s.set_content_cb {
#   s.rputs "hello trusterd world from cb"
#   s.echo "+ hello trusterd world from cb with \n"
# }

#
# f = File.open "#{root_dir}/logs/access.log", "a"
#
# s.set_logging_cb {
#
#   p "callback block after send response"
#   f.write "#{s.conn.client_ip} #{Time.now} - #{s.r.uri} - #{s.r.filename}\n"
#
# }

#
# or use access logging methods
#s.setup_access_log({
#  :file   => "/usr/local/trusterd/logs/access.log",
#
#  # :default or :custom
#  # if using :custom, set logging format to write_access_log mehtod arg
#  # s.write_access_log "client_ip: #{s.client_ip}"
#  :format => :default,
#
#  # :plain or :json if using :default
#  :type   => :plain,
#})
#
#s.set_logging_cb {
#  s.write_access_log
#}

s.run

