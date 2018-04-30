ultimo [x] = x
ultimo (_:xs) = ultimo xs

maior [x] = x
maior (a:b:xs)
    | a > b     = maior (a:xs)
    | otherwise = maior (b:xs)


semultimo [x] = []
semultimo (x:xs) = x : semultimo xs

soma [] = 0
soma (x:xs) = x + soma xs
somapos l = soma [x | x <- l, x > 0]

sorted [] = True
sorted [_] = True
sorted (a:b:xs) = a < b && sorted (b:xs)

shiftright l =  ultimo l : semultimo l

shiftleft (x:xs) = xs ++ [x]

invert [] = []
invert (x:xs) = invert xs ++ [x]

appears _ [] = 0
appears i (x:xs) = should_count + appears xs
   where should_count = (if i == x then 1 else 0)


posaux _ [] _ = -1
posaux a (x:xs) i
   | a == x    = i
   | otherwise = posaux a xs (i+1)

position x l = posaux x l 0

# Queria que funcionasse isso ;-;
# positron a l = head [y | x <- l | y <- [0..(length l)], x == a]

remover a l = [x | x <- l, x /= a]

trocar a b l = [y | x <- l, let y = if x == a then b else x]