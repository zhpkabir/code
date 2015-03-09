int strcmp(const char *a, const char *b) 
{
        while (*a || *b) {
                if (*a != *b) 
                        return 1;
                if (*a == 0 || *b == 0)
                        return 1;
                a++;
                b++;
        }

        return 0;
}

