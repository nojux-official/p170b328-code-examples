defmodule Aggregator do
  use GenServer

  @flush_interval_ms 500  # how often average calculation must happen
  @max_capacity 100  # buffer size limit

  @doc """
  Starts the gen server process
  """

  def start_link() do
    GenServer.start_link(__MODULE__, :ok)
  end

  @doc """
  Initializes the starting state of the gen server
  """

  def init(_opts) do
    # create a timer so that average is computed no later than after required amount. The timer will send a message tick
    # to this gen server
    timer = Process.send_after(self(), :tick, @flush_interval_ms)
    # value count is the amount of values that were used to compute the average
    # average is the aggregated average
    # buffered values is a list of values that were sent to this process but not yet added to the average
    # timer is there because we sometimes need to cancel it
    {:ok, %{value_count: 0, average: 0, buffered_values: [], timer: timer}}
  end

  @doc """
  Adds a new value to the aggregator
  """

  def add_value(pid, value) do
    # a cast message is sent because we don't need the return value
    GenServer.cast(pid, {:add, value})
  end

  @doc """
  A handler for the add cast message. Accepts a value to add and the current state which is destructured. A new value is
  added to the buffer. If buffer size limit is exceeded, the buffer is incorporated to the current average value.
  """

  def handle_cast(
        {:add, value},
        %{value_count: value_count, average: average, buffered_values: buffered_values, timer: timer}
      ) do
    # add the item to the buffer
    updated_values = [value | buffered_values]
    if length(updated_values) > @max_capacity do
      # max capacity is reached, we are adding the buffer to the current average, so the timer is cancelled and a new
      # timer is launched
      Process.cancel_timer(timer)
      %{value_count: total_new_values, average: new_average} = transfer_average(updated_values, value_count, average)
      new_timer = Process.send_after(self(), :tick, @flush_interval_ms)
      # new state contains updated value count and average, buffer is reset to empty and a new timer is added
      {:noreply, %{value_count: total_new_values, average: new_average, buffered_values: [], timer: new_timer}}
    else
      IO.inspect(updated_values)
      {:noreply, %{value_count: value_count, average: average, buffered_values: updated_values, timer: timer}}
    end
  end

  @doc """
  A private function that transfers existing buffered values to the aggregated average
  """

  defp transfer_average(updated_values, value_count, average) do
    # check new item count. If there are no values, nothing is changed
    item_count = length(updated_values)
    if item_count == 0 do
      IO.puts(average)
      %{value_count: value_count, average: average}
    else
      # list is not empty - recompute the average. First, compute the total amount of items, which is previous amount +
      # new buffer size
      total_new_values = value_count + item_count
      # new average is the sum of previous values (value count * average) + sum of added values and divided by the
      # total amount of items
      new_average = (value_count * average + Enum.sum(updated_values)) / total_new_values
      IO.puts(new_average)
      # return the new state
      %{value_count: total_new_values, average: new_average}
    end
  end

  @doc"""
  Handle the tick message from the timer - force average computation from the buffer
  """
  def handle_info(
        :tick,
        %{value_count: value_count, average: average,
          buffered_values: buffered_values} = _state
      ) do
    %{value_count: total_new_values,
      average: new_average} = transfer_average(buffered_values, value_count, average)
    # launch a new timer so that this calculation happens again after the required interval
    new_timer = Process.send_after(self(), :tick, @flush_interval_ms)
    {:noreply, %{value_count: total_new_values, average: new_average,
      buffered_values: [], timer: new_timer}}
  end

end