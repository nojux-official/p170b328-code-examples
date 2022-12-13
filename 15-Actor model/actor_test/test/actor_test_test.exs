defmodule ActorTestTest do
  use ExUnit.Case
  doctest ActorTest

  test "greets the world" do
    assert ActorTest.hello() == :world
  end
end
