# Trabalho Agenda pBuffer

Desafio:\
Agenda\
Faça uma agenda com o seguinte menu:\
1- Adicionar Pessoa (Nome, Idade, email)\
2- Remover Pessoa\
3- Buscar Pessoa\
4- Listar todos\
5- Sair

O desafio é não poder criar variáveis e sim um buffer de memória (void *pBuffer). Nisso vocês terão que fazer o trabalho que o Sistema Operacional faz para vocês ao organizar a memória.

Regras:\
Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.\
Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.\
Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)\
Não pode usar struct em todo o programa.\
Entregar link de um vídeo explicando o código e mostrando alguns testes e ao final o resultado do DrMemory ou Valgrind.\
Vou perguntar no 1:1 sobre a sua implementação. Posso pedir para fazer alguma modificação no código na nossa conversa. O objetivo é saber se entenderam o que fizeram.

## Agenda pBuffer

De acordo com a opção selecionada, será chamada uma função (AdicionarPessoa, RemoverPessoa, BuscarPessoa, ListarTodos) que irá manipular o pBuffer para criação da agenda ou a saída do programa com a chamada de um free(pBuffer).

Caso 1:\
Testando funções AdicionarPessoa, RemoverPessoa e ListarTodos.\
Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 1

Digite o Nome: joao
 
Digite a Idade: 20

Digite seu Email: joao@gmail.com

Usuario cadastrado com sucesso

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 4

Nome: joao
Idade: 20
Email: joao@gmail.com

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 2

Nome da pessoa a remover: joao

Pessoa removida!

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 4

Nenhuma pessoa cadastrada.

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 5

Caso 2:\
Testando função BuscarPessoa.\
Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 3

Nenhuma pessoa cadastrada.

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 1

Digite o Nome: joao
 
Digite a Idade: 20

Digite seu Email: joao@gmail.com

Usuario cadastrado com sucesso

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 3

Nome da pessoa a buscar: joao

Nome: joao
Idade: 20
Email: joao@gmail.com


Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 3

Nome da pessoa a buscar: jorge

Pessoa nao encontrada!

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 2

Nome da pessoa a remover: joao

Pessoa removida!

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 3

Nenhuma pessoa cadastrada.

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 5

Caso 3:\
Verificando se os reallocs estão implementados corretamente.\
Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 1

Digite o Nome: joao
 
Digite a Idade: 20

Digite seu Email: joao@gmail.com

Usuario cadastrado com sucesso

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 1

Digite o Nome: jorge
 
Digite a Idade: 30

Digite seu Email: jorge@gmail.com

Usuario cadastrado com sucesso

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 3

Nome da pessoa a buscar: jorge

Nome: jorge
Idade: 30
Email: jorge@gmail.com


Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 3

Nome da pessoa a buscar: joao

Nome: joao
Idade: 20
Email: joao@gmail.com


Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 2

Nome da pessoa a remover: joao

Pessoa removida!

Menu:
1 - Adicionar Pessoa
2 - Remover Pessoa
3 - Buscar Pessoa
4 - Listar Todos
5 - Sair

Escolha uma opcao: 3

Nome da pessoa a buscar: jorge

Nome: jorge
Idade: 30
Email: jorge@gmail.com


Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 3

Nome da pessoa a buscar: joao

Pessoa nao encontrada!

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 4

Nome: jorge
Idade: 30
Email: jorge@gmail.com

Menu:\
1 - Adicionar Pessoa\
2 - Remover Pessoa\
3 - Buscar Pessoa\
4 - Listar Todos\
5 - Sair

Escolha uma opcao: 5

## Autor

João Vitor Montanher Lago\
E-mail: jvmlago@inf.ufpel.edu.br
