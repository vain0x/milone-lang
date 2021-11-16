drop table if exists documents;

create table documents(uri varchar(1024), version int, text text);
