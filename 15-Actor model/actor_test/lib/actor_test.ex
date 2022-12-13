defmodule ActorTest do
  use Application

  @doc """
    Entry point of the program. Launches 4 processes - counter (contains state), stopper (runs the final action after
    other processes), increase and decrease (sends messages to counter)
  """

  def start(_type, _args) do
    counter = spawn(ActorTest, :count, [0])
    stopper = spawn(ActorTest, :stopper, [0, counter])
    spawn(ActorTest, :increase, [counter, stopper, 50])
    spawn(ActorTest, :decrease, [counter, stopper, 50])

    Task.start(fn -> 0 end)
  end

  @doc """
    May receive 3 types of messages and acts according to the message received
  """

  def count(initial) do
    receive do
      {:increase} -> count(initial + 1)  # increase value and receive another message
      {:decrease} -> count(initial - 1)  # decrease value and receive another message
      {:stop} -> IO.puts initial  # print current value and finish
    end
  end

  @doc """
    Sends increase messages to counter a given number of times. When all increase messages are sent, sends a signal to
    stopper and finishes.
  """

  def increase(counter, stopper, remaining_increases) do
    if remaining_increases > 0 do
      send counter, {:increase}  # send message to counter
      increase(counter, stopper, remaining_increases - 1)  # send one more message
    else
      send stopper, {:stop}  # send the final message to stopper
    end
  end

  @doc """
    Sends decrease messages to counter a given number of times. When all decrease messages are sent, sends a signal to
    stopper and finishes.
  """

  def decrease(counter, stopper, remaining_decreases) do
    if remaining_decreases > 0 do
      send counter, {:decrease}  # send message to counter
      decrease(counter, stopper, remaining_decreases - 1)  # send one more message
    else
      send stopper, {:stop}  # send the final message to stopper
    end
  end

  @doc """
   Receives 2 stop messages from increaser and decreaser and then sends a stop message to counter
  """

  def stopper(stopped_process_count, counter) do
    if stopped_process_count == 2 do
      send counter, {:stop}
    else
      receive do
        {:stop} -> stopper(stopped_process_count + 1, counter)
      end
    end
  end
end
