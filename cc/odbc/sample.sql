DROP TABLE IF EXISTS books;

CREATE TABLE books (
  name CHAR(128),
  page INTEGER
);

INSERT INTO books (name, page)
VALUES
  ('foo', 24),
  (NULL, 12);

