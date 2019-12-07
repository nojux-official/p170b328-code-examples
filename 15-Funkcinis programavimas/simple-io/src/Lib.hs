module Lib
    ( someFunc
    ) where

import           Control.Concurrent

someFunc :: IO ()
someFunc = do
  forkIO (execute "First")
  forkIO (execute "Second")
  execute "Third"

execute :: String -> IO ()
execute name = do
  putStrLn (name ++ ": one")
  putStrLn (name ++ ": two")
  putStrLn (name ++ ": three")
