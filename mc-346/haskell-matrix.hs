
restos m = map tail m

diagonal_principal [] = []
diagonal_principal m = (head . head) m : diagonal_principal (tail $ restos m)

transverse [] = []
transverse m
| null $ head m = []
| otherwise = (map head m) : transverse (restos m)



multiplicar f s = aux f (transverse s)

aux [] _ = []
aux f s = map (\x -> mult x (head f)) s : aux (tail f) s

mult x y = element $ zipWith (*) x y
element l = foldl (\acc x -> x + acc) 0 l
