create table content_versions(
    id bigint not null,
    content_id integer not null,
    title character varying,
    text character varying,
    user_id integer not null,
    created_at timestamp with time zone default now(),
    version integer not null,
    constraint content_versions_id_pkey primary key (id)
);

CREATE SEQUENCE content_versions_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER TABLE ONLY content_versions ALTER COLUMN id SET DEFAULT nextval('content_versions_id_seq'::regclass);

create unique index content_versions_ux on content_versions (content_id, version);
