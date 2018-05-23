import Data.List (sort, lines, group, intercalate)
import Data.Map ((!), insert, adjust, toList, empty)

data Vertex = Vertex String [Float] deriving (Ord, Show)
data Edge = Edge Float Vertex Vertex deriving (Eq, Ord, Show)

instance Eq Vertex where (==) (Vertex x _) (Vertex y _) = x == y

distance :: Vertex -> Vertex -> Float
distance (Vertex _ a) (Vertex _ b) =
  sqrt $ foldl (\acc (x,y) -> acc + (x-y)^2 ) 0 $
  zipWith (\f s -> (f,s) ) a b

edges [] = []
edges (x:xs) = (foldl (\acc y -> (Edge (distance x y) x y) : acc) [] xs) ++ edges xs

init_sets l = foldl (\acc (Vertex key _) -> insert key [key] acc) empty l
same_set m (Vertex first _) (Vertex second _) = (m ! first) == (m ! second)

-- As próximas duas funções unificam o conjunto recentemente adquirido pelo algoritmo
unify [] _ m = m
unify (x:xs) key m = adjust (\_ -> m ! key) x $ unify xs key m

unify_sets m (Vertex first _) (Vertex second _) = unify (new_map ! second) second new_map
  where new_map = adjust (\l -> l ++ (m ! first)) second m

kruskal _ 0  m = m
kruskal [] _ m = m
kruskal ((Edge _ v y):rest) k m
  | same_set m v y = kruskal rest k m
  | otherwise      = kruskal rest (k-1) (unify_sets m v y)


minimal_spanning_tree v k = kruskal (sort $ edges v) ((length v) - k) (init_sets v)

extract_groups l = map head $ group $ sort $ map sort $ map (\(_, x) -> x) $ toList l
convert_vertex   = map (\x -> read x :: Float)

main = do
  c <- getContents

  let contents = lines c
  let k = head contents
  let v = map (\l -> (Vertex (head l) (convert_vertex $ tail l))) (map words (tail contents))
  let g = extract_groups $ minimal_spanning_tree v (read k :: Int)

  putStrLn (intercalate "\n" (map (intercalate " ") g))
