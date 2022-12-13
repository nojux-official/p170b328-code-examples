defmodule Agents do
  use Application

  def start(_args, _type) do
    {:ok, counter} = Agent.start_link(fn -> 0 end)
    stopper = spawn(Agents, :stopper, [0, counter])
    spawn(Agents, :increase, [counter, stopper, 50])
    spawn(Agents, :decrease, [counter, stopper, 50])

    Task.start(fn -> 0 end)
  end

  def increase(counter, stopper, remaining_increases) do
    if remaining_increases > 0 do
      Agent.update(counter, fn (count) -> count + 1 end)
      increase(counter, stopper, remaining_increases - 1)
    else
      send stopper, {:stop}
    end
  end

  def decrease(counter, stopper, remaining_decreases) do
    if remaining_decreases > 0 do
      Agent.update(counter, fn (count) -> count - 1 end)
      decrease(counter, stopper, remaining_decreases - 1)
    else
      send stopper, {:stop}
    end
  end

  def stopper(stopped_process_count, counter) do
    if stopped_process_count == 2 do
      IO.puts Agent.get(counter, fn count -> count end)
    else
      receive do
        {:stop} -> stopper(stopped_process_count + 1, counter)
      end
    end
  end

end
