

redis-start:
	~/opt/redis-3.2.8/bin/redis-server redis.conf

redis-stop:
	kill `cat redis_6379.pid`

sidekiq-start:
	sidekiq --daemon --pidfile ./sidekiq.pid --logfile ./sidekiq.log  --require ./sample_worker.rb

sidekiq-stop:
	kill `cat sidekiq.pid`



