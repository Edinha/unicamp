data Ling = Ling String Int deriving (Show)

naisu (Ling s n) = s


data Vertex = String [Float]
data Edge = Float Vertex Vertex deriving (Ord)

distance :: Vertex -> Vertex -> Float
distance (Vertex _ a) (Vertex _ b) = 
  sqrt $ sum $ foldl (\acc (x,y) -> (x-y)ˆ2 ) 0 $
  zipWith (\f s -> (f,s) ) a b
