BEGIN;

CREATE TABLE patrons
(
    barcode BIGINT NOT NULL UNIQUE,
    name VARCHAR(255) NOT NULL,
    PRIMARY KEY (barcode)
);

INSERT INTO patrons (barcode, name)
VALUES (1011020, 'Bob Wiley'),
       (6732234, 'Dr. Leo Marvin'),
       (8402834, 'Fay Marvin'),
       (8675309, 'Inigo Montoya');


CREATE TABLE books
(
    barcode BIGINT NOT NULL UNIQUE,
    title VARCHAR(255) NOT NULL,
    author VARCHAR(255) NOT NULL,
    description TEXT NOT NULL,
    PRIMARY KEY (barcode)
);

INSERT INTO books (barcode, title, author, description)
VALUES (9781789471625, 'The Llama Who Ate Christmas', 'Wondershop', 'When the festive friends are hungry, can you guess what they eat?. Read this book and you will see their funny Christmas treat!'),
       (9781848699526, 'Where Happiness Lives', 'Barry Timms', 'Three little mice. Three very different houses. But which is the happiest home?'),
       (9781534446380, 'Red Sled', 'Lita Judge', 'Find out what happens when a cast of unlikely woodland friends discover a well-loved sled outside a cozy cabin in this whimsical Classic Board Book.'),
       (9780451474575, 'Llama Llama Red Pajama', 'Anna Dewdney', 'A bedtime story. A good-night kiss. And Mama Llama turns off the light. But is everything all right? No!'),
       (9781594748585, 'Home Alone', 'John Hughes', 'Eight-year-old Kevin McCallister wished his family would disappear. He never thought his wish would come true!');


CREATE TABLE library_books
(
    library_barcode BIGINT NOT NULL UNIQUE,
    book_barcode BIGINT NOT NULL,
    PRIMARY KEY (library_barcode),
    CONSTRAINT fk_book FOREIGN KEY(book_barcode) REFERENCES books(barcode) ON DELETE CASCADE
);

INSERT INTO library_books (library_barcode, book_barcode)
VALUES (5892375234, 9781789471625),
       (5892375235, 9781848699526),
       (5892375236, 9781848699526),
       (5892375237, 9781534446380),
       (5892375238, 9780451474575),
       (5892375239, 9780451474575),
       (5892375240, 9780451474575),
       (5892375241, 9781594748585);


CREATE TABLE loans
(
    id SERIAL NOT NULL,
    library_book_barcode BIGINT NOT NULL,
    patron_barcode BIGINT NOT NULL,
    start_date DATE NOT NULL,
    end_date DATE,
    due_date DATE NOT NULL,
    PRIMARY KEY (id),
    CONSTRAINT fk_library_book FOREIGN KEY(library_book_barcode) REFERENCES library_books(library_barcode) ON DELETE CASCADE,
    CONSTRAINT fk_patron FOREIGN KEY(patron_barcode) REFERENCES patrons(barcode) ON DELETE CASCADE
);

INSERT INTO loans (id, library_book_barcode, patron_barcode, start_date, end_date, due_date)
VALUES (1, 5892375237, 1011020, '1991-05-17', '1991-05-31', '1991-05-31'),
       (2, 5892375241, 1011020, '1990-11-16', '1990-11-20', '1990-11-30'),
       (3, 5892375239, 8402834, '2024-01-26', NULL,         '2024-02-09'),
       (4, 5892375236, 8675309, '2023-12-29', NULL,         '2024-01-12');


COMMIT;