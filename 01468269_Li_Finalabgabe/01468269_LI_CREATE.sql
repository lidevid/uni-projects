CREATE TABLE blumen_geschaeft (
geschaeft_id INTEGER, name VARCHAR(20),
ort VARCHAR(10) NOT NULL, plz INTEGER NOT NULL, strasse VARCHAR(30) NOT NULL, 
PRIMARY KEY(geschaeft_id));

CREATE TABLE blume(
blume_id INTEGER PRIMARY KEY, 
sorte VARCHAR(20) UNIQUE NOT NULL,g_id INTEGER NOT NULL, 
anzahl INTEGER DEFAULT 100,  preise INTEGER,
FOREIGN KEY (g_id) REFERENCES blumen_geschaeft ON DELETE CASCADE);

CREATE TABLE lager(
lager_id INTEGER, g_id INTEGER NOT NULL,
grundflaeche FLOAT, temperatur FLOAT DEFAULT 20,
PRIMARY KEY(lager_id,g_id),
FOREIGN KEY(g_id) REFERENCES blumen_geschaeft ON DELETE CASCADE);

CREATE TABLE einlagern(
lager_id INTEGER, g_id INTEGER,
blume_id VARCHAR(20) REFERENCES blume ON DELETE CASCADE,
lieferungsdatum DATE NOT NULL,
PRIMARY KEY(blume_id, lager_id,g_id),
FOREIGN KEY(lager_id,g_id) REFERENCES lager(lager_id,g_id) ON DELETE CASCADE);

CREATE TABLE mitarbeiter(
prsn_id INTEGER PRIMARY KEY,
vorname VARCHAR(20) NOT NULL, nachname VARCHAR(20) NOT NULL, gehalt INTEGER,
geschlecht VARCHAR(2),                                                                                                                                                                         g_id INTEGER NOT NULL,
FOREIGN KEY (g_id) REFERENCES blumen_geschaeft ON DELETE CASCADE,
CHECK (geschlecht in ('m','w')));

CREATE TABLE is_boss(
boss_id INTEGER, 
mitarbeiter_id INTEGER,
PRIMARY KEY (boss_id, mitarbeiter_id),
FOREIGN KEY (boss_id) REFERENCES mitarbeiter ON DELETE CASCADE,
FOREIGN KEY (mitarbeiter_id) REFERENCES mitarbeiter ON DELETE CASCADE);

CREATE TABLE freelancer(
email VARCHAR(30) , stundenlohn NUMBER(3) DEFAULT 8, stundenanzahl NUMBER(3),
prsn_id INTEGER UNIQUE REFERENCES mitarbeiter ON DELETE CASCADE,
PRIMARY KEY(email));

CREATE TABLE festangestellter(
steuer_nr INTEGER , ueberstunde_anzahl INTEGER,
prsn_id INTEGER UNIQUE REFERENCES mitarbeiter ON DELETE CASCADE,
PRIMARY KEY(steuer_nr));

CREATE TABLE kunde(
kunde_id INTEGER PRIMARY KEY,
vorname VARCHAR(20) NOT NULL, nachname VARCHAR(20) NOT NULL, email VARCHAR(30),
betreuer_pnr INTEGER REFERENCES mitarbeiter ON DELETE CASCADE);


CREATE TABLE lieferant(
firma_id INTEGER PRIMARY KEY,
adresse VARCHAR(50) NOT NULL, name VARCHAR(20) NOT NULL);

CREATE TABLE blumenstrauss(
artikel_nr INTEGER PRIMARY KEY,
name VARCHAR(20) NOT NULL, preise NUMBER(4),
kaufer_id INTEGER REFERENCES kunde ON DELETE CASCADE);

CREATE TABLE blumen_lieferant_strauss(
blume_id INTEGER REFERENCES blume ON DELETE CASCADE,
firma_id INTEGER REFERENCES lieferant ON DELETE CASCADE,
artikel_nr INTEGER REFERENCES blumenstrauss ON DELETE CASCADE,
PRIMARY KEY(blume_id, firma_id, artikel_nr));
