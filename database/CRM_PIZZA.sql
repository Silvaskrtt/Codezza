PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE tbl_Cliente(
    ID_Cliente_PK   VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome            VARCHAR(100), 
    Sobrenome       VARCHAR(100)
);
INSERT INTO tbl_Cliente(
    ID_Cliente_PK,
    Nome,
    Sobrenome) VALUES
        ('CLI001','João',       'Pedro'),
        ('CLI002','Renato',     'Oliveira'),
        ('CLI003','Viviane',    'Chagas'),
        ('CLI004','Manuele',    'Maria'),
        ('CLI005','Ana',        'Silva'),
        ('CLI006','Maria',      'Clara');
CREATE TABLE tbl_Telefone_Cliente(
    ID_Telefone_PK  VARCHAR(10) NOT NULL PRIMARY KEY,
    ID_Cliente_FK   VARCHAR(10),
    Num_Telefone    INTEGER,

    FOREIGN KEY(ID_Cliente_FK)
        REFERENCES tbl_Cliente(ID_Cliente_PK)
);
INSERT INTO tbl_Telefone_Cliente(
    ID_Telefone_PK,
    Num_Telefone,
    ID_Cliente_FK) VALUES
        ('TEL001','3427443135',     'CLI001'),
        ('TEL002','34993773727',    'CLI001'),
        ('TEL003','9237585001',     'CLI002'),
        ('TEL004','4527431705',     'CLI004'),
        ('TEL005','41999092171',    'CLI005');
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
INSERT INTO tbl_Endereco_Cliente(
    ID_Endereco_PK,
    Rua,
    Num_Casa,
    Bairro,
    Cidade,
    ID_Cliente_FK) VALUES
        ('END001','Rua Oriximiná','549','Marambaia','Belém',                        'CLI001'),
        ('END0002','Vila Sorriso','260','Terra Firme','Belém',                      'CLI002'),
        ('END0003',NULL,NULL,NULL,NULL,                                             'CLI003'),
        ('END0004','Passagem Apiraíba II','989','Maracacuera (Icoaraci)','Belém',   'CLI004'),
        ('END0005','Alameda Quatro','146','Parque Verde','Belém',                   'CLI005'),
        ('END0006',NULL,NULL,NULL,NULL,                                             'CLI006');
CREATE TABLE tbl_Status_Pedido(
    ID_Status_Pedido_PK     VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome_Status_Pedido      VARCHAR(25)
);
INSERT INTO tbl_Status_Pedido(
    ID_Status_Pedido_PK,
    Nome_Status_Pedido) VALUES
        ('STP001',           'Recebido'),
        ('STP002','      Em preparação'),
        ('STP003',  'Saiu para entrega'),
        ('STP004',             'Pronto'),
        ('STP005',           'Entregue'),
        ('STP006',          'Cancelado');
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
INSERT INTO tbl_Pedido(
    ID_Pedido_PK, 
    Data, 
    Hora, 
    ID_Cliente_FK, 
    ID_Status_Pedido_FK) VALUES
        ('PED1001','2025-04-07','20:44:00','CLI003','STP001'),
        ('PED1002','2025-02-05','18:30:00','CLI001','STP001'),
        ('PED1003','2025-03-13','21:00:00','CLI006','STP001'),
        ('PED1004','2025-01-04','19:30:00','CLI005','STP004'),
        ('PED1005','2025-07-05','19:30:00','CLI002','STP005'),
        ('PED1006','2025-04-07','19:30:00','CLI004','STP006');
CREATE TABLE tbl_Tipo_Pizza(
    ID_Tipo_Pizza_PK    VARCHAR(10) NOT NULL PRIMARY KEY, 
    Nome_Tipo           VARCHAR(25)
);
INSERT INTO tbl_Tipo_Pizza(
    ID_Tipo_Pizza_PK,
    Nome_Tipo) VALUES
        ('TPI001',           'Doce'),
        ('TPI002',        'Salgada'),
        ('TPI003',  'Personalizado');
CREATE TABLE tbl_Sabor_Pizza(
    ID_Sabor_PK         VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome_Pizza          VARCHAR(100),
    Preco               NUMERIC, 
    ID_Tipo_Pizza_FK    VARCHAR(10),

    FOREIGN KEY(ID_Tipo_Pizza_FK)
        REFERENCES tbl_Tipo_Pizza(ID_Tipo_Pizza_PK)
);
INSERT INTO tbl_Sabor_Pizza(
    ID_Sabor_PK,
    Nome_Pizza,
    Preco,
    ID_Tipo_Pizza_FK) VALUES
        ('PZ001','Hello World de Chocolate',34.89,   'TPI001'),
        ('PZ002','Loop Frango BBQ',39.89,            'TPI002'),
        ('PZ003','Commit de Camarão',52.89,          'TPI002'),
        ('PZ004','Null Veggie',36.89,                'TPI002'),
        ('PZ005','Try-Catch Trufado',38.89,          'TPI001'),
        ('PZ006','404 - Pizza Not Found',44.89,      'TPI003');
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
INSERT INTO tbl_Itens_Pedido(
    ID_Item_PK,
    Qtd,
    Preco_Unit,
    ID_Sabor_FK,
    ID_Pedido_FK) VALUES
        ('ITM0001',2,34.89,'PZ001','PED1001'),
        ('ITM0002',5,52.89,'PZ003','PED1002'),
        ('ITM0003',1,39.89,'PZ002','PED1003'),
        ('ITM0004',3,38.89,'PZ005','PED1004'),
        ('ITM0005',3,44.89,'PZ006','PED1005'),
        ('ITM0006',1,44.89,'PZ006','PED1006');
CREATE TABLE tbl_Ingredientes(
    ID_Ingrediente_PK   VARCHAR(10) NOT NULL PRIMARY KEY, 
    Nome_Ingrediente    VARCHAR(100)
);
INSERT INTO tbl_Ingredientes(
    ID_Ingrediente_PK,
    Nome_Ingrediente) VALUES
        ('ING001',        'Creme de avelã'),
        ('ING002',   'Raspas de chocolate'),
        ('ING003',  'Granulados coloridos'),
        ('ING004',       'Frango desfiado'),
        ('ING005',        'Molho barbecue'),
        ('ING006',                 'Milho'),
        ('ING007',    'Camarões grelhados'),
        ('ING008',             'Abobrinha'),
        ('ING009',    'Brigadeiro trufado'),
        ('ING010',                  'Alho'),
        ('ING011',           'Raspa limão'),
        ('ING012',              'Pimentão'),
        ('ING013',         'Tomate-cereja'),
        ('ING014',            'Champignon');
CREATE TABLE tbl_Pizza_Ingredientes(
    ID_Pizza_Ingrediente_PK     VARCHAR(10) NOT NULL PRIMARY KEY,
    ID_Sabor_FK                 VARCHAR(10),
    ID_Ingrediente_FK           VARCHAR(10),

    FOREIGN KEY(ID_Sabor_FK)
        REFERENCES tbl_Sabor_Pizza(ID_Sabor_PK),

    FOREIGN KEY(ID_Ingrediente_FK)
        REFERENCES tbl_Ingredientes(ID_Ingrediente_PK)
);
INSERT INTO tbl_Pizza_Ingredientes(
    ID_Pizza_Ingrediente_PK,
    ID_Sabor_FK,
    ID_Ingrediente_FK) VALUES
        ('REL001','PZ001','ING001'),
        ('REL002','PZ001','ING002'),
        ('REL003','PZ001','ING003'),
        ('REL004','PZ002','ING004'),
        ('REL005','PZ002','ING005'),
        ('REL006','PZ002','ING006'),
        ('REL007','PZ003','ING007'),
        ('REL008','PZ003','ING010'),
        ('REL009','PZ003','ING011'),
        ('REL010','PZ004','ING008'),
        ('REL011','PZ004','ING012'),
        ('REL012','PZ004','ING013'),
        ('REL013','PZ004','ING014'),
        ('REL014','PZ005','ING009');
CREATE TABLE tbl_Status_Comanda(
    ID_Status_Comanda_PK    VARCHAR(10) NOT NULL PRIMARY KEY,
    Nome_Status_Comanda     VARCHAR(100)
);
INSERT INTO tbl_Status_Comanda(
    ID_Status_Comanda_PK,
    Nome_Status_Comanda) VALUES
        ('STC001',     'Aberta'),
        ('STC002',    'Fechada'),
        ('STC003',  'Cancelada');
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
INSERT INTO tbl_Comanda(
    ID_Comanda_PK,
    Hora_Abertura,
    Data_Fechamento,
    Hora_Fechamento,
    ID_Cliente_FK,
    ID_Pedido_FK,
    ID_Status_Comanda_FK) VALUES
    ('COM0001','20:44:00','2025-04-07','20:55:00','CLI001','PED1001','STC001'),
    ('COM0002','18:30:00','2025-02-05','20:30:00','CLI002','PED1002','STC001'),
    ('COM0003','21:00:00','2025-03-13','22:10:00','CLI003','PED1003','STC001'),
    ('COM0004','19:30:00','2025-01-04','20:30:00','CLI004','PED1004','STC001'),
    ('COM0005','19:30:00','2025-07-05','21:30:00','CLI005','PED1005','STC002'),
    ('COM0006','19:30:00','2025-04-07','19:37:00','CLI006','PED1006','STC003');
COMMIT;