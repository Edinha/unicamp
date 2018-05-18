import Data.List (sort)
import Data.Map (findWithDefault, insert, adjust, union, empty)

data Vertex = Vertex String [Float] String deriving (Ord, Show)
data Edge = Edge Float Vertex Vertex deriving (Eq, Ord, Show)

instance Eq Vertex where (==) (Vertex x _ _) (Vertex y _ _) = x == y

distance :: Vertex -> Vertex -> Float
distance (Vertex _ a _) (Vertex _ b _) =
  sqrt $ foldl (\acc (x,y) -> acc + (x-y)^2 ) 0 $
  zipWith (\f s -> (f,s) ) a b

edges [] = []
edges (x:xs) = (foldl (\acc y -> (Edge (distance x y) x y) : acc) [] xs) ++ edges xs

get_edges l = sort $ edges l

-- get_edges [ (Vertex "a" [0, 0] "a"), (Vertex "b" [0, 1] "b"), (Vertex "c" [0, 2] "b") ]

init_sets [] = empty
init_sets ((Vertex a b _):rest) = Data.Map.insert a (Vertex a b a) (init_sets rest)

same_set m (Vertex first _ _) (Vertex second _ _) = a == b
  where (Vertex _ _ a) = findWithDefault (Vertex "" [] "") first m
        (Vertex _ _ b) = findWithDefault (Vertex "" [] "") second m

unify_sets m (Vertex _ _ a) (Vertex second p _) = adjust (\ _ -> (Vertex second p a)) second m

kruskal _ 0  m = m
kruskal [] _ m = m
kruskal ((Edge _ v y):rest) k m
  | same_set m v y = kruskal rest k m
  | otherwise      = kruskal rest (k-1) (unify_sets m v y)


minimal_spanning_tree e v k = kruskal e ((length v) - k) (init_sets v)
