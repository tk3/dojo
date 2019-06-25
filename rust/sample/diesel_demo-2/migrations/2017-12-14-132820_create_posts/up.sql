CREATE TABLE posts (
  id         INT           AUTO_INCREMENT NOT NULL PRIMARY KEY,
  title      VARCHAR(256)  NOT NULL,
  body       VARCHAR(256)  NOT NULL,
  published  BOOLEAN       NOT NULL
)
