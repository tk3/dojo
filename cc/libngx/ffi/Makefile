CC       = gcc

SOURCES  = sample.c

OBJS     = $(SOURCES:.c=.o)

NGINX_OBJS =  \
        ./nginx-1.11.1/objs/src/core/ngx_log.o \
        ./nginx-1.11.1/objs/src/core/ngx_palloc.o \
        ./nginx-1.11.1/objs/src/core/ngx_array.o \
        ./nginx-1.11.1/objs/src/core/ngx_list.o \
        ./nginx-1.11.1/objs/src/core/ngx_hash.o \
        ./nginx-1.11.1/objs/src/core/ngx_buf.o \
        ./nginx-1.11.1/objs/src/core/ngx_queue.o \
        ./nginx-1.11.1/objs/src/core/ngx_output_chain.o \
        ./nginx-1.11.1/objs/src/core/ngx_string.o \
        ./nginx-1.11.1/objs/src/core/ngx_parse.o \
        ./nginx-1.11.1/objs/src/core/ngx_parse_time.o \
        ./nginx-1.11.1/objs/src/core/ngx_inet.o \
        ./nginx-1.11.1/objs/src/core/ngx_file.o \
        ./nginx-1.11.1/objs/src/core/ngx_crc32.o \
        ./nginx-1.11.1/objs/src/core/ngx_murmurhash.o \
        ./nginx-1.11.1/objs/src/core/ngx_md5.o \
        ./nginx-1.11.1/objs/src/core/ngx_rbtree.o \
        ./nginx-1.11.1/objs/src/core/ngx_radix_tree.o \
        ./nginx-1.11.1/objs/src/core/ngx_slab.o \
        ./nginx-1.11.1/objs/src/core/ngx_times.o \
        ./nginx-1.11.1/objs/src/core/ngx_shmtx.o \
        ./nginx-1.11.1/objs/src/core/ngx_connection.o \
        ./nginx-1.11.1/objs/src/core/ngx_cycle.o \
        ./nginx-1.11.1/objs/src/core/ngx_spinlock.o \
        ./nginx-1.11.1/objs/src/core/ngx_rwlock.o \
        ./nginx-1.11.1/objs/src/core/ngx_cpuinfo.o \
        ./nginx-1.11.1/objs/src/core/ngx_conf_file.o \
        ./nginx-1.11.1/objs/src/core/ngx_module.o \
        ./nginx-1.11.1/objs/src/core/ngx_resolver.o \
        ./nginx-1.11.1/objs/src/core/ngx_open_file_cache.o \
        ./nginx-1.11.1/objs/src/core/ngx_crypt.o \
        ./nginx-1.11.1/objs/src/core/ngx_proxy_protocol.o \
        ./nginx-1.11.1/objs/src/core/ngx_syslog.o \
        ./nginx-1.11.1/objs/src/event/ngx_event.o \
        ./nginx-1.11.1/objs/src/event/ngx_event_timer.o \
        ./nginx-1.11.1/objs/src/event/ngx_event_posted.o \
        ./nginx-1.11.1/objs/src/event/ngx_event_accept.o \
        ./nginx-1.11.1/objs/src/event/ngx_event_connect.o \
        ./nginx-1.11.1/objs/src/event/ngx_event_pipe.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_time.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_errno.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_alloc.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_files.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_socket.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_recv.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_readv_chain.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_udp_recv.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_send.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_writev_chain.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_udp_send.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_channel.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_shmem.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_process.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_daemon.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_setaffinity.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_setproctitle.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_posix_init.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_user.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_dlopen.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_process_cycle.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_linux_init.o \
        ./nginx-1.11.1/objs/src/event/modules/ngx_epoll_module.o \
        ./nginx-1.11.1/objs/src/os/unix/ngx_linux_sendfile_chain.o \
        ./nginx-1.11.1/objs/src/event/ngx_event_openssl.o \
        ./nginx-1.11.1/objs/src/event/ngx_event_openssl_stapling.o \
        ./nginx-1.11.1/objs/src/core/ngx_regex.o \
        ./nginx-1.11.1/objs/src/http/ngx_http.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_core_module.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_special_response.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_request.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_parse.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_log_module.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_request_body.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_variables.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_script.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_upstream.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_upstream_round_robin.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_file_cache.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_write_filter_module.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_header_filter_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_chunked_filter_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_range_filter_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_gzip_filter_module.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_postpone_filter_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_ssi_filter_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_charset_filter_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_userid_filter_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_headers_filter_module.o \
        ./nginx-1.11.1/objs/src/http/ngx_http_copy_filter_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_not_modified_filter_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_static_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_autoindex_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_index_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_auth_basic_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_access_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_limit_conn_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_limit_req_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_geo_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_map_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_split_clients_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_referer_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_rewrite_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_ssl_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_proxy_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_fastcgi_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_uwsgi_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_scgi_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_memcached_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_empty_gif_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_browser_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_upstream_hash_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_upstream_ip_hash_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_upstream_least_conn_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_upstream_keepalive_module.o \
        ./nginx-1.11.1/objs/src/http/modules/ngx_http_upstream_zone_module.o \
        ./nginx-1.11.1/objs/ngx_modules.o 

INCLUDES =  \
   -I./nginx-1.11.1/src/core  \
   -I./nginx-1.11.1/objs  \
   -I./nginx-1.11.1/src/os/unix  \
   -I./nginx-1.11.1/src/event  \
   $(shell pkg-config --cflags libffi)

CFLAGS   = -Wall

LDFLAGS  = -ldl -lpthread -lcrypt -lpcre -lssl -lcrypto -ldl -lz  \
    $(shell pkg-config --libs libffi)

LIBS     =

TARGET   = main


$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(NGINX_OBJS) $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

debug:
	make -f Makefile CFLAGS="-g $(CFLAGS)" LDFLAGS="-g $(LDFLAGS)"

clean:
	rm -f $(TARGET) $(OBJS)

get_nginx:
	curl -O https://nginx.org/download/nginx-1.11.1.tar.gz

build_nginx:
	cd nginx-1.11.1;  \
	./configure --with-http_ssl_module;  \
	make

