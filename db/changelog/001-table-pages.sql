create table pages (
    id integer not null,
    content_id integer not null,
    slug character varying,
    created_at timestamp with time zone default now(),
    constraint pages_id_pkey primary key (id)
);

CREATE SEQUENCE pages_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER TABLE ONLY pages ALTER COLUMN id SET DEFAULT nextval('pages_id_seq'::regclass);

create unique index pages_slug_ux on pages (slug);
