PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE tbl_Cliente(
    ID_Cliente VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome VARCHAR(100),
    Sobrenome VARCHAR(100)
);
INSERT INTO tbl_Cliente VALUES('CLI001','João','Pedro');
INSERT INTO tbl_Cliente VALUES('CLI002','Renato','Oliveira');
INSERT INTO tbl_Cliente VALUES('CLI003','Viviane','Chagas');
INSERT INTO tbl_Cliente VALUES('CLI004','Manuele','Maria');
INSERT INTO tbl_Cliente VALUES('CLI005','Ana','Silva');
INSERT INTO tbl_Cliente VALUES('CLI006','Maria','Clara');
CREATE TABLE tbl_Telefone_Cliente(
    ID_Telefone_PK VARCHAR(10) NOT NULL PRIMARY KEY,
    ID_Cliente_FK VARCHAR(10),
    Num_Telefone INT(11),
    FOREIGN KEY(ID_Cliente_FK) REFERENCES tbl_Cliente(ID_Cliente)
);
INSERT INTO tbl_Telefone_Cliente VALUES('TEL001','3427443135','CLI001');
INSERT INTO tbl_Telefone_Cliente VALUES('TEL002','34993773727','CLI001');
INSERT INTO tbl_Telefone_Cliente VALUES('TEL003','9237585001','CLI002');
INSERT INTO tbl_Telefone_Cliente VALUES('TEL004','4527431705','CLI004');
INSERT INTO tbl_Telefone_Cliente VALUES('TEL005','41999092171','CLI005');
COMMIT;
