require "sidekiq"
require "./sample_worker"

puts SampleWorker

Sidekiq::Client.enqueue SampleWorker, 'call enqueue', 100

SampleWorker.perform_async 'call perform', 200

