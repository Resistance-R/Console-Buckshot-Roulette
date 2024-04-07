    printf("\n\n재장전!\n\n");

    for(int i = 0; i < shells; i++)
    {
        srand(time(NULL));

        int BlankOrLive = rand() % ;

        printf("%d", BlankOrLive);

        shotgun[i] = BlankOrLive;

        if(shotgun[i] == 0)
        {
            blank++;
        }

        else if(shotgun[i] == 1)
        {
            live++;
        }
    }