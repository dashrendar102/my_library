BEGIN;

CREATE TABLE patrons
(
    id SERIAL NOT NULL,
    name VARCHAR(255) NOT NULL,
    barcode INTEGER NOT NULL UNIQUE,
    PRIMARY KEY (id)
);

INSERT INTO patrons (id, name, barcode)
VALUES (1, 'Bob Wiley',      1011020),
       (2, 'Dr. Leo Marvin', 6732234),
       (3, 'Fay Marvin',     8402834),
       (4, 'Inigo Montoya',  8675309);

SELECT SETVAL('patrons_id_seq', 10);


CREATE TABLE books
(
    id SERIAL NOT NULL,
    barcode BIGINT NOT NULL UNIQUE,
    title VARCHAR(255) NOT NULL,
    author VARCHAR(255) NOT NULL,
    description TEXT NOT NULL,
    PRIMARY KEY (id)
);

INSERT INTO books (id, barcode, title, author, description)
VALUES (1, 9781789471625, 'The Llama Who Ate Christmas', 'Wondershop', 'When the festive friends are hungry, can you guess what they eat?. Read this book and you will see their funny Christmas treat!'),
       (2, 9781848699526, 'Where Happiness Lives', 'Barry Timms', 'Three little mice. Three very different houses. But which is the happiest home?'),
       (3, 9781534446380, 'Red Sled', 'Lita Judge', 'Find out what happens when a cast of unlikely woodland friends discover a well-loved sled outside a cozy cabin in this whimsical Classic Board Book.'),
       (4, 9780451474575, 'Llama Llama Red Pajama', 'Anna Dewdney', 'A bedtime story. A good-night kiss. And Mama Llama turns off the light. But is everything all right? No!'),
       (5, 9781594748585, 'Home Alone', 'John Hughes', 'Eight-year-old Kevin McCallister wished his family would disappear. He never thought his wish would come true!');

SELECT SETVAL('books_id_seq', 10);

CREATE TABLE library_books
(
    id SERIAL NOT NULL,
    library_barcode BIGINT NOT NULL UNIQUE,
    book_id INTEGER NOT NULL,
    PRIMARY KEY (id),
    CONSTRAINT fk_book FOREIGN KEY(book_id) REFERENCES books(id) ON DELETE CASCADE
);

INSERT INTO library_books (id, library_barcode, book_id)
VALUES (1, 5892375234, 1),
       (2, 5892375235, 2),
       (3, 5892375236, 2),
       (4, 5892375237, 3),
       (5, 5892375238, 4),
       (6, 5892375239, 4),
       (7, 5892375240, 4),
       (8, 5892375241, 5);

SELECT SETVAL('library_books_id_seq', 20);

CREATE TABLE loans
(
    id SERIAL NOT NULL,
    library_book_id INTEGER NOT NULL,
    patron_id INTEGER NOT NULL,
    start_date DATE NOT NULL,
    end_date DATE,
    due_date DATE NOT NULL,
    PRIMARY KEY (id),
    CONSTRAINT fk_library_book FOREIGN KEY(library_book_id) REFERENCES library_books(id) ON DELETE CASCADE,
    CONSTRAINT fk_patron FOREIGN KEY(patron_id) REFERENCES patrons(id) ON DELETE CASCADE
);

INSERT INTO loans (id, library_book_id, patron_id, start_date, end_date, due_date)
VALUES (1, 4, 1, '1991-05-17', '1991-05-31', '1991-05-31'),
       (2, 8, 1, '1990-11-16', '1990-11-20', '1990-11-30'),
       (3, 6, 3, '2024-01-26', NULL,         '2024-02-09'),
       (4, 3, 4, '2023-12-29', NULL,         '2024-01-12');

SELECT SETVAL('loans_id_seq', 10);

COMMIT;