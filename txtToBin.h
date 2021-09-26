
//REFERENCIA: https://stackoverflow.com/questions/12911299/read-csv-file-in-c
const char *getfield(char *line, int num)
{
  const char *tok;
  for (tok = strtok(line, ";"); tok && *tok && num; tok = strtok(NULL, ";\n\r"))
    num--;

  return tok;
}

//REFERENCIA: https://stackoverflow.com/questions/12911299/read-csv-file-in-c
void geraBinario()
{
  FILE *stream = fopen("input.CSV", "r");
  if (stream != NULL)
  {
    FILE *arqBin = fopen("relatorio.dat", "wb");
    if (arqBin != NULL)
    {
      
      char line[300];
      char *tmp = NULL;
      input in;

      while (fgets(line, 300, stream))
      {
        
        tmp = strdup(line);
        in.cod = atoi(getfield(tmp, 0));
        free(tmp);

        tmp = strdup(line);
        strcpy(in.nome, getfield(tmp, 1));
        free(tmp);

        tmp = strdup(line);
        strcpy(in.ende, getfield(tmp, 2));
        free(tmp);

        tmp = strdup(line);
        strcpy(in.bairro, getfield(tmp, 3));
        free(tmp);

        tmp = strdup(line);
        strcpy(in.estado, getfield(tmp, 4));
        free(tmp);

        tmp = strdup(line);
        strcpy(in.cidade, getfield(tmp, 5));
        free(tmp);
        

        /*
        for (size_t i = 0; i < 6; i++)
        {
          tmp = strdup(line);
          printf("[%s]", getfield(tmp, i));
          free(tmp);
        }
        putchar('\n');
        */

        fwrite(&in, sizeof(input), 1, arqBin);
      }
      fclose(arqBin);
    }
    else
      perror("Erro (arqBin)");

    fclose(stream);
  }
  else
    perror("Erro (ArqCsv)");
}