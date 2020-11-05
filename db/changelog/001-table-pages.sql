create table pages (
    id integer not null,
    content_id integer not null,
    slug character varying,
    created_at timestamp with time zone,
    constraint pages_id_pkey primary key (id)
);
