SELECT movies.title
    FROM movies
    LEFT JOIN stars
    ON movies.id = stars.movie_id 
    WHERE stars.person_id in (307, 136)
    GROUP BY movies.id
    HAVING COUNT(movies.id) >= 2;
