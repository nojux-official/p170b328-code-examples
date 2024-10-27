defmodule AsyncExample do
  use Application
  # Function to calculate the factorial of a number
  defp factorial(n) when n >= 0, do: Enum.reduce(1..n, 1, &(&1*&2))

  # Function that demonstrates async/await with factorial computation
  def start(_args, _type) do
    # Asynchronously calculate the factorial of three different numbers
    task1 = Task.async(fn -> factorial(50) end)
    task2 = Task.async(fn -> factorial(70) end)
    task3 = Task.async(fn -> factorial(100) end)

    # Wait for the tasks to complete and get their results
    result1 = Task.await(task1)
    result2 = Task.await(task2)
    result3 = Task.await(task3)

    IO.puts "Factorials: #{result1}, #{result2}, #{result3}"
    Task.start(fn -> 0 end)
  end
end
