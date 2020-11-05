create table content_versions(
    id bigint not null,
    content_id integer not null,
    title character varying,
    text character varying,
    user_id integer not null,
    created_at timestamp with time zone,
    version integer not null,
    constraint content_versions_id_pkey primary key (id)
);
