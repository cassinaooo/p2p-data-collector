## Um protocolo de aplicação para transporte de dados utilizando VANTs.

### Contexto 

Métodos de sensoriamento autônomo de áreas remotas, críticas ou perigosas tem sido utilizados em larga escala em projetos de pesquisa e comerciais para aumentar a eficiência no uso dos recursos humanos envolvidos. Dispositivos computacionais equipados com diversos sensores produzem dados importantes para o monitoramento dessas áreas, em um volume considerável. Métodos usuais de transporte de dados entre os sensores e entre os sensores e os interessados em geral são dificultados pelas condições ambientais envolvidas. Links de satélite ou transmissão direta dos dados podem ser inviáveis técnica e economicamente, além de aumentar o consumo de energia, um fator crítico em tais sistemas.

### Solução

Esta aplicação busca possibilitar a transmissão de dados genéricos entre equipamentos sensoriais instalados em áreas remotas (i.e Raspberry Pi 3 com câmeras e microfones instalados na floresta), com Veículos Aéreos Não-Tripulados autônomos (i.e Quadrotor Asctec Pelican). 

Essa comunicação se dá através de uma rede adhoc entre os dispositivos. O Raspberry que possui os dados a serem transmitidos detecta a presença do VANT próximo, e inicia a transmissão de seus dados. 

O Raspberry inicia a comunicação, e após o sucesso na conexão ao drone, compacta os arquivos na pasta especificada em um único e inicia a transmissão deste através da rede utilizando TCP. O drone recebe a stream do arquivo, e o armazena no disco local.

Finalizado o recebimento dos arquivos, o VANT retorna à base com os dados para os interessados, e ambos os equipamentos terminam a transação em um estado de "pronto" para a transação seguinte.

### Implementação

A aplicação utilizada do lado do Raspberry é chamada de "sender" nesta arquitetura, e a aplicação que roda no lado do drone é chamda de "receiver". Estas são acessíveis através dos binários ```./bin/sender``` e ```./bin/receiver```, respectivamente.

É possível produzir os binários utilizando a utilidade unix ```make```.

### Decisões de projeto

O sender aguarda um diretório como entrada, no qual todos os arquivos a serem enviados devem estar contidos. O diretório será convertido em um arquivo no diretório pai ```<pasta>_<timestamp>.tar.gz```, de acordo com o horário local no dispositivo sender. 
Esse arquivo será removido da pasta, assim como os arquivos que o geraram, ao sucesso da transação.

O receiver armazena os dados recebidos no diretório especificado como paramêtro, sendo cada transação sendo armazenada neste diretório como ```<hostname>/<timestamp>/<arquivo>```