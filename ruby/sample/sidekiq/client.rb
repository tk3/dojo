
require "sidekiq"
require "./sample_worker"

puts SampleWorker

Sidekiq::Client.enqueue(SampleWorker, 'bob', 1)

