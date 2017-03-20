require "sidekiq"

class SampleWorker
  include Sidekiq::Worker

  def perform(*args)
    puts "SampleWorker arguments #{args.map(&:inspect).join(', ')}"
  end
end
