module Lib
    ( getSum
    ) where

getVector :: [Integer]
getVector = take 20 [1,2..]

getSum :: Integer
getSum =
  vectorSum where
    vector = getVector
    -- filter only even numbers
    filteredVector = filter even vector
    -- map to squares
    squaredVector = map (\x -> x * x) filteredVector
    -- reduce to product
    vectorSum = foldl (+) 0 squaredVector
