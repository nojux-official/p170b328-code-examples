defmodule GenServerExample do
  use Application

  @doc """
  A program that creates a gen server and sends items to it at different intervals. The gen server has a buffer that
  holds the values until either a limit of value count is reached or timeout is reached, and then computes the average
  """

  def start(_type, _args) do
    values_to_send = Enum.to_list(0..1000)
    # start gen server
    {:ok, aggregator} = Aggregator.start_link()
    # send values with different timeouts
    Enum.each values_to_send, fn value ->
      Aggregator.add_value(aggregator, value)
      timeout = Integer.floor_div(value, 10)
      Process.sleep(timeout)
    end
    Process.sleep(600)
    Task.start(fn -> 0 end)
  end
end
