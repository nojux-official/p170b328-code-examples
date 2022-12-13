defmodule GenServerExampleTest do
  use ExUnit.Case
  doctest GenServerExample

  test "greets the world" do
    assert GenServerExample.hello() == :world
  end
end
