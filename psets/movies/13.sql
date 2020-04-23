SELECT people.name
    FROM movies
    JOIN stars
    ON movies.id = stars.movie_id
    JOIN people
    ON people.id = stars.person_id
    WHERE stars.movie_id in (SELECT movies.id
        FROM movies
        JOIN stars
        ON movies.id = stars.movie_id
        WHERE stars.person_id = 102
        GROUP BY movies.id)
    AND NOT stars.person_id = 102
    GROUP BY people.id;


-- TEST CASE
-- -- 欲しい情報
-- -- person.name
-- -- Kevin BeaconのID
-- SELECT id
--     FROM people
--     WHERE name = "Kevin Bacon"
--     AND birth = 1958;
-- -- OUT : 102

-- -- "Kevin Bacon"出演の映画
-- SELECT movies.id
--     FROM movies
--     JOIN stars
--     ON movies.id = stars.movie_id
--     WHERE stars.person_id = 102;
    
-- -- -- "Kevin Bacon"出演の映画に出演した人物
-- SELECT COUNT(*)
-- FROM(
-- SELECT people.name
--     FROM movies
--     JOIN stars
--     ON movies.id = stars.movie_id
--     JOIN people
--     ON people.id = stars.person_id
--     WHERE stars.movie_id in (SELECT movies.id
--         FROM movies
--         JOIN stars
--         ON movies.id = stars.movie_id
--         WHERE stars.person_id = 102
--         GROUP BY movies.id)
--     AND NOT stars.person_id = 102
--     GROUP BY people.id);