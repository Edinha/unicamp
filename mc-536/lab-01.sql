SELECT nome FROM pessoa where ano_nascimento <> 1981;



SELECT p.nome as pessoa, c.nome as cidade, v.data, v.custo FROM pessoa p

INNER JOIN viagem v ON v.id_pessoa = p.id

INNER JOIN cidade c ON v.id_cidade = c.id;



SELECT c.nome, p.nome FROM cidade c

INNER JOIN pessoa p ON p.nasceu = c.id

WHERE p.sexo = 'F';



SELECT c.id, c.nome FROM cidade c WHERE c.id NOT IN (SELECT nasceu FROM pessoa);



SELECT p.nome FROM pessoa p ORDER BY ano_nascimento LIMIT 1;



SELECT p.nome || ' ' || p.sobrenome FROM pessoa p

INNER JOIN cidade c ON c.id = p.nasceu

WHERE c.nome = 'Campinas';



SELECT (count(v)::float / (SELECT COUNT(*) FROM viagem)) AS c, p.nome FROM pessoa p

INNER JOIN viagem v ON p.id = v.id_pessoa

GROUP BY p.id

ORDER BY c;



SELECT c.nome, COUNT(*) as result FROM pessoa p

INNER JOIN cidade c ON c.id = p.nasceu

GROUP BY c.id

HAVING COUNT(*) > 1;


