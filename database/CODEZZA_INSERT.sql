PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE tbl_Cliente(
    ID_Cliente_PK   VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome            VARCHAR(100), 
    Sobrenome       VARCHAR(100)
);
INSERT INTO tbl_Cliente VALUES('CLI001','João','Pedro');
INSERT INTO tbl_Cliente VALUES('CLI002','Renato','Oliveira');
INSERT INTO tbl_Cliente VALUES('CLI003','Viviane','Chagas');
INSERT INTO tbl_Cliente VALUES('CLI004','Manuele','Maria');
INSERT INTO tbl_Cliente VALUES('CLI005','Ana','Silva');
INSERT INTO tbl_Cliente VALUES('CLI006','Maria','Clara');
CREATE TABLE tbl_Telefone_Cliente(
    ID_Telefone_PK  VARCHAR(10) NOT NULL PRIMARY KEY,
    ID_Cliente_FK   VARCHAR(10),
    Num_Telefone    INTEGER,

    FOREIGN KEY(ID_Cliente_FK)
        REFERENCES tbl_Cliente(ID_Cliente_PK)
);
INSERT INTO tbl_Telefone_Cliente VALUES('TEL001','CLI001',3427443135);
INSERT INTO tbl_Telefone_Cliente VALUES('TEL002','CLI001',34993773727);
INSERT INTO tbl_Telefone_Cliente VALUES('TEL003','CLI002',9237585001);
INSERT INTO tbl_Telefone_Cliente VALUES('TEL004','CLI004',4527431705);
INSERT INTO tbl_Telefone_Cliente VALUES('TEL005','CLI005',41999092171);
CREATE TABLE tbl_Endereco_Cliente(
    ID_Endereco_PK   VARCHAR(10) NOT NULL PRIMARY KEY,
    Rua              VARCHAR(50),
    Num_Casa         VARCHAR(10),
    Bairro           VARCHAR(50),
    Cidade           VARCHAR(50),
    ID_Cliente_FK    VARCHAR(10),

    FOREIGN KEY(ID_Cliente_FK)
        REFERENCES tbl_Cliente(ID_Cliente_PK)
);
INSERT INTO tbl_Endereco_Cliente VALUES('END001','Rua Oriximiná','549','Marambaia','Belém','CLI001');
INSERT INTO tbl_Endereco_Cliente VALUES('END0002','Vila Sorriso','260','Terra Firme','Belém','CLI002');
INSERT INTO tbl_Endereco_Cliente VALUES('END0003',NULL,NULL,NULL,NULL,'CLI003');
INSERT INTO tbl_Endereco_Cliente VALUES('END0004','Passagem Apiraíba II','989','Maracacuera (Icoaraci)','Belém','CLI004');
INSERT INTO tbl_Endereco_Cliente VALUES('END0005','Alameda Quatro','146','Parque Verde','Belém','CLI005');
INSERT INTO tbl_Endereco_Cliente VALUES('END0006',NULL,NULL,NULL,NULL,'CLI006');
CREATE TABLE tbl_Status_Pedido(
    ID_Status_Pedido_PK     VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome_Status_Pedido      VARCHAR(25)
);
INSERT INTO tbl_Status_Pedido VALUES('STP001','Recebido');
INSERT INTO tbl_Status_Pedido VALUES('STP002','      Em preparação');
INSERT INTO tbl_Status_Pedido VALUES('STP003','Saiu para entrega');
INSERT INTO tbl_Status_Pedido VALUES('STP004','Pronto');
INSERT INTO tbl_Status_Pedido VALUES('STP005','Entregue');
INSERT INTO tbl_Status_Pedido VALUES('STP006','Cancelado');
CREATE TABLE tbl_Pedido(
    ID_Pedido_PK            VARCHAR(10) NOT NULL PRIMARY KEY,
    Data                    DATE,
    Hora                    TIME,
    ID_Cliente_FK           VARCHAR(10),
    ID_Status_Pedido_FK     VARCHAR(10),

    FOREIGN KEY(ID_Cliente_FK)
        REFERENCES tbl_Cliente(ID_Cliente_PK),

    FOREIGN KEY(ID_Status_Pedido_FK)
        REFERENCES tbl_Status_Pedido(ID_Status_Pedido_PK)
);
INSERT INTO tbl_Pedido VALUES('PED1001','2025-04-07','20:44:00','CLI003','STP001');
INSERT INTO tbl_Pedido VALUES('PED1002','2025-02-05','18:30:00','CLI001','STP001');
INSERT INTO tbl_Pedido VALUES('PED1003','2025-03-13','21:00:00','CLI006','STP001');
INSERT INTO tbl_Pedido VALUES('PED1004','2025-01-04','19:30:00','CLI005','STP004');
INSERT INTO tbl_Pedido VALUES('PED1005','2025-07-05','19:30:00','CLI002','STP005');
INSERT INTO tbl_Pedido VALUES('PED1006','2025-04-07','19:30:00','CLI004','STP006');
CREATE TABLE tbl_Tipo_Pizza(
    ID_Tipo_Pizza_PK    VARCHAR(10) NOT NULL PRIMARY KEY, 
    Nome_Tipo           VARCHAR(25)
);
INSERT INTO tbl_Tipo_Pizza VALUES('TPI001','Doce');
INSERT INTO tbl_Tipo_Pizza VALUES('TPI002','Salgada');
INSERT INTO tbl_Tipo_Pizza VALUES('TPI003','Personalizado');
CREATE TABLE tbl_Sabor_Pizza(
    ID_Sabor_PK         VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome_Pizza          VARCHAR(100),
    Preco               NUMERIC, 
    ID_Tipo_Pizza_FK    VARCHAR(10),

    FOREIGN KEY(ID_Tipo_Pizza_FK)
        REFERENCES tbl_Tipo_Pizza(ID_Tipo_Pizza_PK)
);
INSERT INTO tbl_Sabor_Pizza VALUES('PZ001','Hello World de Chocolate',34.89000000000000056,'TPI001');
INSERT INTO tbl_Sabor_Pizza VALUES('PZ002','Loop Frango BBQ',39.89000000000000056,'TPI002');
INSERT INTO tbl_Sabor_Pizza VALUES('PZ003','Commit de Camarão',52.89000000000000056,'TPI002');
INSERT INTO tbl_Sabor_Pizza VALUES('PZ004','Null Veggie',36.89000000000000056,'TPI002');
INSERT INTO tbl_Sabor_Pizza VALUES('PZ005','Try-Catch Trufado',38.89000000000000056,'TPI001');
INSERT INTO tbl_Sabor_Pizza VALUES('PZ006','404 - Pizza Not Found',44.89000000000000056,'TPI003');
CREATE TABLE IF NOT EXISTS "tbl_Itens_Pedido"(
    ID_Item_PK      VARCHAR(10) NOT NULL PRIMARY KEY,
    Qtd             INT,
    Preco_Unit      NUMERIC,
    ID_Sabor_FK     VARCHAR(10),
    ID_Pedido_FK    VARCHAR(10),

    FOREIGN KEY(ID_Sabor_FK)
        REFERENCES tbl_Sabor_Pizza(ID_Sabor_PK),

    FOREIGN KEY(ID_Pedido_FK)
        REFERENCES tbl_Pedido(ID_Pedido_PK)
);
INSERT INTO tbl_Itens_Pedido VALUES('ITM0001',2,34.89000000000000056,'PZ001','PED1001');
INSERT INTO tbl_Itens_Pedido VALUES('ITM0002',5,52.89000000000000056,'PZ003','PED1002');
INSERT INTO tbl_Itens_Pedido VALUES('ITM0003',1,39.89000000000000056,'PZ002','PED1003');
INSERT INTO tbl_Itens_Pedido VALUES('ITM0004',3,38.89000000000000056,'PZ005','PED1004');
INSERT INTO tbl_Itens_Pedido VALUES('ITM0005',3,44.89000000000000056,'PZ006','PED1005');
INSERT INTO tbl_Itens_Pedido VALUES('ITM0006',1,44.89000000000000056,'PZ006','PED1006');
CREATE TABLE tbl_Ingredientes(
    ID_Ingrediente_PK   VARCHAR(10) NOT NULL PRIMARY KEY, 
    Nome_Ingrediente    VARCHAR(100)
);
INSERT INTO tbl_Ingredientes VALUES('ING001','Creme de avelã');
INSERT INTO tbl_Ingredientes VALUES('ING002','Raspas de chocolate');
INSERT INTO tbl_Ingredientes VALUES('ING003','Granulados coloridos');
INSERT INTO tbl_Ingredientes VALUES('ING004','Frango desfiado');
INSERT INTO tbl_Ingredientes VALUES('ING005','Molho barbecue');
INSERT INTO tbl_Ingredientes VALUES('ING006','Milho');
INSERT INTO tbl_Ingredientes VALUES('ING007','Camarões grelhados');
INSERT INTO tbl_Ingredientes VALUES('ING008','Abobrinha');
INSERT INTO tbl_Ingredientes VALUES('ING009','Brigadeiro trufado');
INSERT INTO tbl_Ingredientes VALUES('ING010','Alho');
INSERT INTO tbl_Ingredientes VALUES('ING011','Raspa limão');
INSERT INTO tbl_Ingredientes VALUES('ING012','Pimentão');
INSERT INTO tbl_Ingredientes VALUES('ING013','Tomate-cereja');
INSERT INTO tbl_Ingredientes VALUES('ING014','Champignon');
CREATE TABLE tbl_Pizza_Ingredientes(
    ID_Pizza_Ingrediente_PK     VARCHAR(10) NOT NULL PRIMARY KEY,
    ID_Sabor_FK                 VARCHAR(10),
    ID_Ingrediente_FK           VARCHAR(10),

    FOREIGN KEY(ID_Sabor_FK)
        REFERENCES tbl_Sabor_Pizza(ID_Sabor_PK),

    FOREIGN KEY(ID_Ingrediente_FK)
        REFERENCES tbl_Ingredientes(ID_Ingrediente_PK)
);
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL001','PZ001','ING001');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL002','PZ001','ING002');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL003','PZ001','ING003');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL004','PZ002','ING004');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL005','PZ002','ING005');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL006','PZ002','ING006');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL007','PZ003','ING007');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL008','PZ003','ING010');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL009','PZ003','ING011');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL010','PZ004','ING008');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL011','PZ004','ING012');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL012','PZ004','ING013');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL013','PZ004','ING014');
INSERT INTO tbl_Pizza_Ingredientes VALUES('REL014','PZ005','ING009');
CREATE TABLE tbl_Status_Comanda(
    ID_Status_Comanda_PK    VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome_Status_Comanda     VARCHAR(100)
);
INSERT INTO tbl_Status_Comanda VALUES('STC001','Aberta');
INSERT INTO tbl_Status_Comanda VALUES('STC002','Fechada');
INSERT INTO tbl_Status_Comanda VALUES('STC003','Cancelada');
CREATE TABLE tbl_Comanda(
    ID_Comanda_PK           VARCHAR(10) NOT NULL PRIMARY KEY,
    Hora_Abertura           TIME,
    Data_Fechamento         DATE,
    Hora_Fechamento         TIME,
    ID_Cliente_FK           VARCHAR(10),
    ID_Pedido_FK            VARCHAR(10),
    ID_Status_Comanda_FK    VARCHAR(10),
    
    FOREIGN KEY(ID_Cliente_FK)
        REFERENCES tbl_Cliente(ID_Cliente_PK),
        
    FOREIGN KEY(ID_Pedido_FK)
        REFERENCES tbl_Pedido(ID_Pedido_PK),
        
    FOREIGN KEY(ID_Status_Comanda_FK)
        REFERENCES tbl_Status_Comanda(ID_Status_Comanda_PK)
);
INSERT INTO tbl_Comanda VALUES('COM0001','20:44:00','2025-04-07','20:55:00','CLI001','PED1001','STC001');
INSERT INTO tbl_Comanda VALUES('COM0002','18:30:00','2025-02-05','20:30:00','CLI002','PED1002','STC001');
INSERT INTO tbl_Comanda VALUES('COM0003','21:00:00','2025-03-13','22:10:00','CLI003','PED1003','STC001');
INSERT INTO tbl_Comanda VALUES('COM0004','19:30:00','2025-01-04','20:30:00','CLI004','PED1004','STC001');
INSERT INTO tbl_Comanda VALUES('COM0005','19:30:00','2025-07-05','21:30:00','CLI005','PED1005','STC002');
INSERT INTO tbl_Comanda VALUES('COM0006','19:30:00','2025-04-07','19:37:00','CLI006','PED1006','STC003');
COMMIT;
