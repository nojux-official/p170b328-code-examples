module Lib
    ( someFunc
    ) where

import           Control.Concurrent
import           Control.Concurrent.MVar
import           Control.Monad

data Counter = Counter (MVar Int)

initCounter :: IO Counter
initCounter = do
  m <- newMVar 0
  let counter = Counter m
  return counter


changeCounter :: Counter -> Int -> IO ()
changeCounter (Counter m) modifier = do
  counterValue <- takeMVar m
  putMVar m (counterValue + modifier)


getCounterValue :: Counter -> IO Int
getCounterValue (Counter m) = do
  counterValue <- takeMVar m
  return counterValue


runIncreaser :: Counter -> MVar () -> IO ()
runIncreaser counter waiter = do
  forM_ [1..100000] $ \i -> do
    changeCounter counter 1
  putMVar waiter ()


runDecreaser :: Counter -> MVar () -> IO ()
runDecreaser counter waiter = do
  forM_ [1..100000] $ \i -> do
    changeCounter counter (-1)
  putMVar waiter ()


someFunc :: IO ()
someFunc = do
  waiter <- newEmptyMVar
  counter <- initCounter
  forM_ [1..10] $ \i -> do
    forkIO (runIncreaser counter waiter)
  forM_ [11..19] $ \i -> do
    forkIO (runDecreaser counter waiter)
  forM_ [1..19] $ \i -> do
    takeMVar waiter
    return ()
  counterValue <- getCounterValue counter
  print counterValue
