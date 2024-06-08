//Modify at your own risk
//git- @Rhythm113

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_PLAYLISTS 100
#define MAX_MUSIC 100

typedef struct _music {
    int id;
    char name[50];
    char artist[50];
    unsigned int release;
    char url[256];
} music;

typedef struct _playlist {
    char name[50];
    music list[MAX_MUSIC]; // max 100 music
    int music_count;
} playlist;

playlist playlists[MAX_PLAYLISTS];
int playlist_count = 0;


void open_url(music *data){
    char olm[512];
    strcpy(olm, "start ");
    strcat(olm, data->url);
    system(olm);
}

void save_playlists(){
    FILE *fp = fopen("db.bin", "wb");
    fwrite(&playlist_count, sizeof(int), 1, fp);
    fwrite(playlists, sizeof(playlist), playlist_count, fp);
    fclose(fp);
}

void load_playlists(){
    FILE *fp = fopen("db.bin", "rb");
    if (fp == NULL) return;
    fread(&playlist_count, sizeof(int), 1, fp);
    fread(playlists, sizeof(playlist), playlist_count, fp);
    fclose(fp);
}

void list_playlists(){
    printf("\nList of Playlists:\n");
    for (int i = 0; i < playlist_count; i++) {
        printf("%d. %s\n", i + 1, playlists[i].name);
    }
}

void add_playlist(){
    if (playlist_count >= MAX_PLAYLISTS) {
        printf("Maximum number of playlists reached!\n");
        return;
    }
    playlist new_playlist;
    printf("Enter the name of the new playlist: ");
    scanf(" %s", new_playlist.name);
    new_playlist.music_count = 0;
    playlists[playlist_count++] = new_playlist;
    save_playlists();
    printf("Playlist '%s' added successfully!\n", new_playlist.name);
}

void edit_playlist(){
    list_playlists();
    printf("Choose a playlist to edit (1-%d): ", playlist_count);
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > playlist_count) {
        printf("Invalid choice!\n");
        return;
    }
    playlist *pl = &playlists[choice - 1];
    printf("Editing playlist: %s\n", pl->name);
    printf("1. Add music\n");
    printf("2. Remove music\n");
    printf("3. List music\n");
    printf("Choose an option (1-3): ");
    int opt;
    scanf("%d", &opt);
    if (opt == 1) {
        if (pl->music_count >= MAX_MUSIC) {
            printf("Playlist is full!\n");
            return;
        }
        music m;
        printf("Enter music ID: ");
        scanf("%d", &m.id);
        printf("Enter music name: ");
        scanf(" %s", m.name);
        printf("Enter artist name: ");
        scanf(" %s", m.artist);
        printf("Enter release year: ");
        scanf("%u", &m.release);
        printf("Enter URL: ");
        scanf(" %s", m.url);
        pl->list[pl->music_count++] = m;
    } else if (opt == 2) {
        for (int i = 0; i < pl->music_count; i++) {
            printf("%d. %s - %s\n", i + 1, pl->list[i].name, pl->list[i].artist);
        }
        printf("Choose a music to remove (1-%d): ", pl->music_count);
        int rm;
        scanf("%d", &rm);
        if (rm < 1 || rm > pl->music_count) {
            printf("Invalid choice!\n");
            return;
        }
        for (int i = rm - 1; i < pl->music_count - 1; i++) {
            pl->list[i] = pl->list[i + 1];
        }
        pl->music_count--;
    } else if (opt == 3) {
        for (int i = 0; i < pl->music_count; i++) {
            printf("%d. %s - %s (%u) [URL: %s]\n", i + 1, pl->list[i].name, pl->list[i].artist, pl->list[i].release, pl->list[i].url);
        }
    } else {
        printf("Invalid option!\n");
    }
    save_playlists();
}

void delete_playlist(){
    list_playlists();
    printf("Choose a playlist to delete (1-%d): ", playlist_count);
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > playlist_count) {
        printf("Invalid choice!\n");
        return;
    }
    for (int i = choice - 1; i < playlist_count - 1; i++) {
        playlists[i] = playlists[i + 1];
    }
    playlist_count--;
    save_playlists();
}


void view_playlist() {
    list_playlists();
    printf("Choose a playlist to view (1-%d): ", playlist_count);
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > playlist_count) {
        printf("Invalid choice!\n");
        return;
    }
    playlist *pl = &playlists[choice - 1];
    printf("Viewing playlist: %s\n", pl->name);
    for (int i = 0; i < pl->music_count; i++) {
        printf("%d. %s - %s (%u) [URL: %s]\n", i + 1, pl->list[i].name, pl->list[i].artist, pl->list[i].release, pl->list[i].url);
    }
    printf("Choose a music to play (1-%d) or 0 to go back: ", pl->music_count);
    int music_choice;
    scanf("%d", &music_choice);
    if (music_choice < 0 || music_choice > pl->music_count) {
        printf("Invalid choice!\n");
        return;
    }
    if (music_choice > 0) {
        open_url(&pl->list[music_choice - 1]);
    }
}



int main() {
    load_playlists();
    //system("cls");
    while (1) {
        printf("\t\t\t=====================================\n");
        printf("\t\t\tMusic Management System 1.0\n");
        printf("\t\t\tAuthor : Zarifa The Topper\n");
        printf("\t\t\t=====================================\n");
        printf("\t\t\t1. List all playlists\n");
        printf("\t\t\t2. Add a Playlist\n");
        printf("\t\t\t3. Edit a Playlist\n");
        printf("\t\t\t4. Delete a playlist\n");
        printf("\t\t\t5. View a playlist\n");
        printf("\t\t\t6. Exit\n");
        printf("\n\n\t\t\tChoose between (1-6) : ");
        int n;
        scanf("%d", &n);
        switch (n) {
            case 1:
                list_playlists();
                break;
            case 2:
                add_playlist();
                break;
            case 3:
                edit_playlist();
                break;
            case 4:
                delete_playlist();
                break;
            case 5:
                view_playlist();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
