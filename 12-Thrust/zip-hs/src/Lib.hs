module Lib
    ( app
    ) where

import System.Random (randomRIO)

randomList :: Int -> IO([Int])
randomList 0 = return []
randomList n = do
  r  <- randomRIO (1,50)
  rs <- randomList (n-1)
  return (r:rs)

app :: IO ()
app = do
  vector1 <- randomList 50
  vector2 <- randomList 50
  print $ zipWith (+) vector1 vector2
