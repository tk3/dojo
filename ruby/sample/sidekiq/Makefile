redis-start:
	~/opt/redis-3.2.8/bin/redis-server ./redis/redis.conf

redis-stop:
	kill `cat ./redis/redis_6379.pid`

sidekiq-start:
	sidekiq --daemon --pidfile ./sidekiq/sidekiq.pid --logfile ./sidekiq/sidekiq.log  --require ./sample_worker.rb

sidekiq-stop:
	kill `cat ./sidekiq/sidekiq.pid`

sidekiq-client:
	ruby sidekiq_client.rb

