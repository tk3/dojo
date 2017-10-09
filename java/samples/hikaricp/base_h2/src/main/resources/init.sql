CREATE TABLE books (
	  id            int PRIMARY KEY,
	  title         varchar(32) NOT NULL,
	  author        varchar(32) NOT NULL,
	  price         integer,
	  release_date  date
);

INSERT INTO books VALUES (1,  'book 01', 'Audrey',   1200, '2015-02-05');
INSERT INTO books VALUES (2,  'book 02', 'Riddhe',   1000, '2017-01-09');
INSERT INTO books VALUES (3,  'book 03', 'Jonah',     500, '2016-06-26');
INSERT INTO books VALUES (4,  'book 04', 'Martha',    480, '2012-10-11');
INSERT INTO books VALUES (5,  'book 05', 'Thomas',    920, '2000-09-03');
INSERT INTO books VALUES (6,  'book 06', 'Morpheus', 1080, '2011-07-09');
INSERT INTO books VALUES (7,  'book 07', 'Agent',    2250, '2008-02-06');
INSERT INTO books VALUES (8,  'book 08', 'Dozer',     250, '2017-03-13');
INSERT INTO books VALUES (9,  'book 09', 'Cypher',    300, '2001-08-22');
INSERT INTO books VALUES (10, 'book 10', 'Tank',      500, '2005-11-28');

