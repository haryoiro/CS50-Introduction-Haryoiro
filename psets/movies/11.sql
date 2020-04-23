SELECT movies.title, ratings.rating 
    FROM people
    JOIN stars
    ON stars.person_id = people.id
    JOIN movies
    ON movies.id = stars.movie_id
    JOIN ratings
    ON movies.id = ratings.movie_id
    WHERE  stars.person_id = 1569276
    ORDER BY ratings.rating DESC
    LIMIT 5;
