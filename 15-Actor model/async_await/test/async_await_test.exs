defmodule AsyncAwaitTest do
  use ExUnit.Case
  doctest AsyncAwait

  test "greets the world" do
    assert AsyncAwait.hello() == :world
  end
end
