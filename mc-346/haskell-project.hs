import Data.List (sort, lines, groupBy, sortBy, intercalate)
import Data.Map ((!), findWithDefault, insert, adjust, toList, empty, delete)
import Data.List.Split (splitOn)

data Vertex = Vertex String [Float] deriving (Ord, Show)
data Edge = Edge Float Vertex Vertex deriving (Eq, Ord, Show)

instance Eq Vertex where (==) (Vertex x _) (Vertex y _) = x == y

distance :: Vertex -> Vertex -> Float
distance (Vertex _ a) (Vertex _ b) =
  sqrt $ foldl (\acc (x,y) -> acc + (x-y)^2 ) 0 $
  zipWith (\f s -> (f,s) ) a b

edges [] = []
edges (x:xs) = (foldl (\acc y -> (Edge (distance x y) x y) : acc) [] xs) ++ edges xs

get_edges l = sort $ edges l

init_sets l = foldl (\acc (Vertex key _) -> insert key [key] acc) empty l
same_set m (Vertex first _) (Vertex second _) = (findWithDefault [] first m) == (findWithDefault [] second m)

unify_sets m (Vertex first _) (Vertex second _)
  | null first_group = delete first $ adjust (\l -> first_group ++ l) second m
  | otherwise        = delete second $ adjust (\l -> second_group ++ l) first m
  where first_group = findWithDefault [] first m
        second_group = findWithDefault [] second m

kruskal _ 0  m = m
kruskal [] _ m = m
kruskal ((Edge _ v y):rest) k m
  | same_set m v y = kruskal rest k m
  | otherwise      = kruskal rest (k-1) (unify_sets m v y)


minimal_spanning_tree e v k = kruskal e ((length v) - (k - 1)) (init_sets v)

extract_groups l = map (\(_, x) -> x) $ toList l

main = do
  c <- getContents

  let contents = lines c
  let k = head contents
  let v = []

  -- TODO read vertexes

  putStrLn "k"
  putStrLn k

  -- TODO example of graph entry, run in ghci
  -- get_edges [ (Vertex "a" [0, 0] "a"), (Vertex "b" [0, 1] "b"), (Vertex "c" [0, 2] "c") ]
