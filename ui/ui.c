#include <gtk-3.0/gtk/gtk.h>

#include "../include/ui.h"
#include "../include/processeur.h"

/**********************************************************
*                   FONCTIONS PRIVÉES
**********************************************************/
/**
 * Mise à jour des de l'affichage des registres
 */
void update_les_label_registre(void);

/**
 * Exécute une instruction à la fois lors de l'appel
 */
void execute_instruction(void);

/**
 * Construit tous les éléments necéssaires
 */
void run_build(void);
/**********************************************************/

#define WIDTH 800
#define HEIGHT 600

t_processeur *processeur;
t_instruction instruction;

gchar *nom_fichier;
gchar *repertoire_fichier;

//Créer une nouvelle fenêtre et cadre
GtkWidget *window;
GtkWidget *fixed_win;

//Créer le boutons de selection de fichier
GtkWidget *hbox_dialog;
GtkWidget *hbox_dialog_btn;
GtkWidget *dialog_btn;
GtkWidget *dialog_entry;

//Créer le choix du mode de simulation
GtkWidget *hbox_mode;
GtkWidget *mode_lbl;
GtkWidget *mode_c;
GtkWidget *mode_p;
GtkWidget *mode_d;

//Créer les boutons de simulation
GtkWidget *start_btn;
GtkWidget *stop_btn;
GtkWidget *next_btn;
GtkWidget *reset_btn;
GtkWidget *close_btn;

GtkWidget *hbox_next_prev_btn;
GtkWidget *next_btn_img;
GtkWidget *prev_btn;
GtkWidget *prev_btn_img;

//Debug
GtkWidget *hbox_debug;
GtkWidget *debug_btn;
GtkWidget *debug_entry;


//Créer les deux boîtes qui séparent l'instruction et les cases mémoires
GtkWidget *data_box;
GtkWidget *inst_box;
GtkWidget *mem_box;
GtkWidget *hbox_data;
GtkWidget *hbox_data_sep;

GtkWidget *inst_grid;
GtkWidget *mem_grid;

GList *data_box_list;
GList *l;
GtkWidget *inst_lbl, *inst_data,
        *cmd_lbl, *cmd_data,
        *dest_lbl, *dest_data,
        *src1_lbl, *src1_data,
        *src2_lbl, *src2_data,
        *val_lbl, *val_data,
        *pc_lbl, *pc_data,
        *x1_lbl, *x1_data,
        *x2_lbl, *x2_data,
        *x3_lbl, *x3_data,
        *x4_lbl, *x4_data,
        *x5_lbl, *x5_data,
        *x6_lbl, *x6_data,
        *x7_lbl, *x7_data,
        *x8_lbl, *x8_data,
        *x9_lbl, *x9_data,
        *x10_lbl, *x10_data,
        *x11_lbl, *x11_data,
        *x12_lbl, *x12_data,
        *x13_lbl, *x13_data,
        *x14_lbl, *x14_data,
        *x15_lbl, *x15_data,
        *space;

GtkWidget *pbar;


void on_file_selection()
{
    GtkWidget *dialog;
    GtkFileFilter *filtre;

    dialog = gtk_file_chooser_dialog_new("Open File",
                                         GTK_WINDOW(window),
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "_Open",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "../input");

    filtre = gtk_file_filter_new();
    gtk_file_filter_set_name(filtre, "*.txt");
    gtk_file_filter_add_pattern(filtre, "*.txt");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filtre);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        repertoire_fichier = gtk_file_chooser_get_filename(chooser);
        nom_fichier = g_path_get_basename(repertoire_fichier);
        //changer le texte de l'entry
        gtk_entry_set_text(GTK_ENTRY(dialog_entry), nom_fichier);
        //reactiver le bouton start
        gtk_widget_destroy(dialog);
        run_build();
    }
    else
    {
        gtk_widget_destroy(dialog);
    }
}

gboolean on_build(gpointer user_data)
{
    GtkWidget *progress_bar = user_data;

    /*Get the current progress*/
    gdouble fraction;
    fraction = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(progress_bar));

    /*Increase the bar by 10% each time this function is called*/
    fraction += 0.1;

    /*Fill in the bar with the new fraction*/
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), fraction);

    /*Ensures that the fraction stays below 1.0*/
    if (fraction < 1.0)
    {
        return TRUE;
    }

    gtk_widget_hide(pbar);
    //réactiver les boutons next et previous
    gtk_widget_set_sensitive(hbox_next_prev_btn, TRUE);
    //réactiver le choix de mode
    gtk_widget_set_sensitive(hbox_mode, TRUE);
    //réactiver le bouton de reset
    gtk_widget_set_sensitive(reset_btn, TRUE);
    //réactiver le bouton de stop
    gtk_widget_set_sensitive(start_btn, TRUE);

    update_les_label_registre();

    return FALSE;
}

void run_build()
{
    processeur = creer_processeur();
    t_instruction_bloc *instruction_bloc = assemblage_instructions(
            repertoire_fichier);
    decode_tableau_instructions(instruction_bloc->instructions,
                                instruction_bloc->nb_instructions);
    processeur->instructions = instruction_bloc->instructions;
    processeur->nb_instructions = instruction_bloc->nb_instructions;

    //désactiver le choix de fichier
    gtk_widget_set_sensitive(hbox_dialog, FALSE);

    pbar = gtk_progress_bar_new();
    gtk_widget_set_name(pbar, "pbar");
    gtk_fixed_put(GTK_FIXED(fixed_win), pbar, 0, 0);
    gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(pbar), 0.5);
    gtk_widget_show(pbar);

    g_timeout_add(200, on_build, GTK_PROGRESS_BAR(pbar));
}


void next_clicked()
{
    if ((gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mode_p)) == TRUE ||
         gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mode_d)) == TRUE) &&
        strcmp(instruction.nom, "ECALL") != 0)
    {
        execute_instruction();
    }
}


void prev_clicked()
{
    processeur->pc = 0;

    for (int i = 0; i < --processeur->nb_instructions_executees; i++)
    {
        execute_instruction();
    }
}


void debug_clicked()
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mode_d)) == TRUE)
    {
        int i = 0;
        const gchar *val = gtk_entry_get_text(GTK_ENTRY(debug_entry));

        i = atoi(val);

        if (i < processeur->nb_instructions_executees &&
            i < processeur->nb_instructions)
        {
            processeur->pc = 0;

            for (int k = 0; k < i; k++)
            {
                execute_instruction();
            }
        }
        else if (i > processeur->nb_instructions_executees &&
                 i < processeur->nb_instructions)
        {
            for (int k = 0; k != i; k++)
            {
                execute_instruction();
            }
        }
    }
}


void on_mode_selection()
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mode_c)) == TRUE)
    {
        gtk_widget_hide(hbox_debug);
        gtk_widget_hide(hbox_next_prev_btn);
        gtk_fixed_move(GTK_FIXED(fixed_win), data_box, 140, 255);

    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mode_p)) == TRUE)
    {
        gtk_widget_hide(hbox_debug);
        gtk_widget_show(hbox_next_prev_btn);
        gtk_fixed_move(GTK_FIXED(fixed_win), data_box, 140, 295);
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mode_d)) == TRUE)
    {
        gtk_widget_show(hbox_debug);
        gtk_widget_show(hbox_next_prev_btn);
        gtk_fixed_move(GTK_FIXED(fixed_win), data_box, 140, 295);
    }
}


/**
 * Permet de construire le tableau d'instruction à partir d'un fichier
 */
void on_start()
{
    /********************************/
    if (strcmp(nom_fichier, "strlen_bin.txt") == 0)
    {
        printf("%s \n", nom_fichier);

        char ets[32];
        strcpy(ets, "Ecole de technologie superieure\0");

        for (int i = 0; i <= 31; i++)
        {
            processeur->memoire[4194304 + i] = (uint8_t)ets[i];

            printf("val = 0x%x   addr = %d\n", processeur->memoire[4194304 + i], i + 4194304);
        }
    }

    if (strcmp(nom_fichier, "fmul_bin.txt") == 0)
    {
        processeur->memoire[4194304] = 0x40;
        processeur->memoire[4194304+1] = 0x49;
        processeur->memoire[4194304+2] = 0x0f;
        processeur->memoire[4194304+3] = 0xdb;

        processeur->memoire[4194308] = 0x44;
        processeur->memoire[4194308+1] = 0x9f;
        processeur->memoire[4194308+2] = 0x2e;
        processeur->memoire[4194308+3] = 0x14;

        processeur->memoire[4194312] = 0x7F;
        processeur->memoire[4194312+1] = 0x80;
        processeur->memoire[4194312+2] = 0x00;
        processeur->memoire[4194312+3] = 0x00;

        processeur->memoire[4194316] = 0x00;
        processeur->memoire[4194316+1] = 0x7F;
        processeur->memoire[4194316+2] = 0xFF;
        processeur->memoire[4194316+3] = 0xFF;

    }
    /********************************/


    //desativer le button start et réactive celui de stop
    gtk_widget_set_sensitive(start_btn, FALSE);
    gtk_widget_set_sensitive(stop_btn, TRUE);
    //activer les boutons next et previous
    gtk_widget_set_sensitive(next_btn, TRUE);
    gtk_widget_set_sensitive(prev_btn, TRUE);
    gtk_widget_set_sensitive(reset_btn, FALSE);
    gtk_widget_set_sensitive(hbox_mode, FALSE);

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mode_c)) == TRUE)
    {
        while (strcmp(instruction.nom, "ECALL") != 0)
        {
            execute_instruction();
        }
    }
}


/**
 * Permet de mettre l'exécution pause
 */
void on_stop()
{
    GList *l;

    //réactive le boutton start et désative celui de stop
    gtk_widget_set_sensitive(start_btn, TRUE);
    gtk_widget_set_sensitive(stop_btn, FALSE);
    //déactiver les boutons next et previous
    gtk_widget_set_sensitive(next_btn, FALSE);
    gtk_widget_set_sensitive(prev_btn, FALSE);
    gtk_widget_set_sensitive(hbox_mode, TRUE);


    gtk_widget_set_sensitive(reset_btn, TRUE);

    processeur->pc = 0;
    processeur->nb_instructions_executees = 0;
    strcpy(instruction.nom, "");
    remise_a_zero_registre(processeur->registres);
    update_les_label_registre();

    int i = 0;
    for (l = g_list_nth(data_box_list, 0); i != 5; l = l->next, i++)
    {
        gtk_label_set_text(l->data, "none");
    }
}


/**
 * Détruit (ferme) la fenêtre de l'application lorsque le X du coin est appuyé.
 */
void on_reset()
{
    gtk_widget_set_sensitive(hbox_dialog, TRUE);
    gtk_widget_set_sensitive(hbox_mode, FALSE);
    gtk_widget_set_sensitive(hbox_next_prev_btn, FALSE);
    gtk_widget_set_sensitive(start_btn, FALSE);
    gtk_widget_set_sensitive(stop_btn, FALSE);
    gtk_widget_set_sensitive(reset_btn, FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (mode_c), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (mode_p), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (mode_d), FALSE);
    gtk_entry_set_text(GTK_ENTRY(dialog_entry), "");
}


void on_close(GApplication *app)
{
    free(processeur->instructions);
    free(processeur);
    processeur = NULL;
    g_application_quit(app);
}


void on_activate(GtkApplication *app)
{
    //fichier CSS à intégrer
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider,
                                    "../ui/simriscrv32em_theme.css",
                                    NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(css_provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    /****************************************************************
     *                  FENÊTRE GÉNÉRALE
     ****************************************************************/
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Simulation RISC RV32EM");
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    //Ajouter le layout fixe à la fenêtre
    fixed_win = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed_win);

    /****************************************************************
    *                  SELECTION DU FICHIER
    ****************************************************************/
    //les boîtes
    hbox_dialog = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(hbox_dialog, "hbox_dialog");
    hbox_dialog_btn = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(hbox_dialog_btn, "hbox_dialog_btn");

    //le bouton d'ouverture de fichier
    dialog_btn = gtk_button_new_with_label("Ouvrir");
    gtk_widget_set_name(dialog_btn, "dialog_btn");

    //afficher le nom du fichier
    dialog_entry = gtk_entry_new();
    gtk_widget_set_name(dialog_entry, "dialog_entry");
    gtk_entry_set_placeholder_text(GTK_ENTRY(dialog_entry), "nom du fichier");
    gtk_entry_set_alignment(GTK_ENTRY(dialog_entry), 0.5);
    gtk_entry_get_icon_name(GTK_ENTRY(dialog_entry), GTK_ENTRY_ICON_PRIMARY);

    //alignement des composante dans les boîtes
    //la boîte du bouton
    gtk_box_pack_start(GTK_BOX(hbox_dialog_btn), dialog_btn, FALSE, FALSE, 0);
    //la boîte mère
    gtk_box_pack_start(GTK_BOX(hbox_dialog), hbox_dialog_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_dialog), dialog_entry, FALSE, FALSE, 0);

    gtk_fixed_put(GTK_FIXED(fixed_win), hbox_dialog, 285, 15);

    /****************************************************************
    *           Ajout des boutons radio (choix du mode)
    ****************************************************************/
    //boîte qui contient les 3 composantes
    hbox_mode = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    //lable
    mode_lbl = gtk_label_new("Mode: ");
    gtk_widget_set_size_request(mode_lbl, 80, 40);

    //mode c
    mode_c = gtk_radio_button_new_with_label(NULL, "Continu");
    gtk_widget_set_name(mode_c, "mode_c");

    //mode p
    mode_p = gtk_radio_button_new_with_label_from_widget(
            GTK_RADIO_BUTTON(mode_c), "Pas à Pas");
    gtk_widget_set_name(mode_p, "mode_p");

    //mode d
    mode_d = gtk_radio_button_new_with_label_from_widget(
            GTK_RADIO_BUTTON(mode_p), "Debug");
    gtk_widget_set_name(mode_d, "mode_d");

    gtk_box_pack_start(GTK_BOX(hbox_mode), mode_lbl, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_mode), mode_c, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_mode), mode_p, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_mode), mode_d, FALSE, FALSE, 0);
    gtk_fixed_put(GTK_FIXED(fixed_win), hbox_mode, 215, 60);

    /****************************************************************
     *                  Ajout des boutons
     ****************************************************************/
    //btn Start
    start_btn = gtk_button_new_with_label("Démarrer");
    gtk_widget_set_name(start_btn, "start_btn");
    gtk_fixed_put(GTK_FIXED(fixed_win), start_btn, 310, 110);
    gtk_widget_set_size_request(start_btn, 80, 50);

    //btn Stop
    stop_btn = gtk_button_new_with_label("Arrêter");
    gtk_widget_set_name(stop_btn, "stop_btn");
    gtk_fixed_put(GTK_FIXED(fixed_win), stop_btn, 415, 110);
    gtk_widget_set_size_request(stop_btn, 80, 50);

    //btn reset
    reset_btn = gtk_button_new_with_label("Reset");
    gtk_widget_set_name(reset_btn, "reset_btn");
    gtk_fixed_put(GTK_FIXED(fixed_win), reset_btn, WIDTH - 190, HEIGHT - 55);
    gtk_widget_set_size_request(reset_btn, 80, 45);

    //btn close
    close_btn = gtk_button_new_with_label("Fermer");
    gtk_widget_set_name(close_btn, "close_btn");
    gtk_fixed_put(GTK_FIXED(fixed_win), close_btn, WIDTH - 95, HEIGHT - 55);
    gtk_widget_set_size_request(close_btn, 80, 45);

    //boîte pour la section debug
    hbox_next_prev_btn = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 35);

    //btn Next
    next_btn_img = gtk_image_new_from_file("../images/next_btn.png");
    next_btn = gtk_button_new_with_label(NULL);
    gtk_button_set_always_show_image(GTK_BUTTON(next_btn), TRUE);
    gtk_button_set_image(GTK_BUTTON(next_btn), next_btn_img);
    gtk_widget_set_name(next_btn, "next_btn");
    gtk_widget_set_size_request(next_btn, 65, 65);
    gtk_widget_set_sensitive(next_btn, FALSE);

    //btn previous
    prev_btn_img = gtk_image_new_from_file("../images/prev_btn.png");
    prev_btn = gtk_button_new_with_label(NULL);
    gtk_button_set_always_show_image(GTK_BUTTON(prev_btn), TRUE);
    gtk_button_set_image(GTK_BUTTON(prev_btn), prev_btn_img);
    gtk_widget_set_name(prev_btn, "prev_btn");
    gtk_widget_set_size_request(prev_btn, 65, 65);
    gtk_widget_set_sensitive(prev_btn, FALSE);

    gtk_box_pack_start(GTK_BOX(hbox_next_prev_btn), prev_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_next_prev_btn), next_btn, FALSE, FALSE, 0);

    gtk_fixed_put(GTK_FIXED(fixed_win), hbox_next_prev_btn, 320, 195);

    /****************************************************************
    *           Ajout de la section debug
    ****************************************************************/
    //boîte pour la section debug
    hbox_debug = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    //btn debug
    debug_btn = gtk_button_new_with_label("Debug");
    gtk_widget_set_name(debug_btn, "debug_btn");
    gtk_widget_set_size_request(debug_btn, 80, 45);

    //debug entry
    debug_entry = gtk_entry_new();
    gtk_widget_set_name(debug_entry, "debug_entry");
    gtk_entry_set_placeholder_text(GTK_ENTRY(debug_entry), "#ligne");
    gtk_entry_set_alignment(GTK_ENTRY(debug_entry), 0.5);
    gtk_widget_set_size_request(debug_entry, 10, 45);

    //insertion dans la boîte
    gtk_box_pack_start(GTK_BOX(hbox_debug), debug_entry, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox_debug), debug_btn, FALSE, FALSE, 0);

    gtk_fixed_put(GTK_FIXED(fixed_win), hbox_debug, 10, HEIGHT - 55);

    /****************************************************************
     *                  GRILLE DES REGISTRES
    ****************************************************************/
    data_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    inst_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    mem_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    hbox_data = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    hbox_data_sep = gtk_separator_new(GTK_ORIENTATION_VERTICAL);

    gtk_box_pack_start(GTK_BOX(data_box), inst_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(data_box), hbox_data_sep, FALSE, FALSE, 55);
    gtk_box_pack_start(GTK_BOX(data_box), mem_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(data_box), hbox_data, FALSE, FALSE, 0);

    gtk_fixed_put(GTK_FIXED(fixed_win), data_box, 140, 255);
    gtk_widget_set_name(data_box, "data_box");

    //les grilles
    inst_grid = gtk_grid_new();
    mem_grid = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(inst_grid), 22);
    gtk_grid_set_column_spacing(GTK_GRID(inst_grid), 20);
    gtk_grid_set_row_spacing(GTK_GRID(mem_grid), 13);
    gtk_grid_set_column_spacing(GTK_GRID(mem_grid), 20);

    gtk_box_pack_start(GTK_BOX(inst_box), inst_grid, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mem_box), mem_grid, FALSE, FALSE, 0);

    inst_lbl = gtk_label_new("Instruction: ");
    inst_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, inst_data);
    cmd_lbl = gtk_label_new("Commande: ");
    cmd_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, cmd_data);
    dest_lbl = gtk_label_new("Destination: ");
    dest_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, dest_data);
    src1_lbl = gtk_label_new("Source1: ");
    src1_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, src1_data);
    src2_lbl = gtk_label_new("Source2: ");
    src2_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, src2_data);
    val_lbl = gtk_label_new("Immédiat: ");
    val_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, val_data);
    pc_lbl = gtk_label_new("PC: ");
    pc_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, pc_data);
    x1_lbl = gtk_label_new("X1: ");
    x1_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x1_data);
    x2_lbl = gtk_label_new("X2: ");
    x2_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x2_data);
    x3_lbl = gtk_label_new("X3: ");
    x3_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x3_data);
    x4_lbl = gtk_label_new("X4: ");
    x4_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x4_data);
    x5_lbl = gtk_label_new("X5: ");
    x5_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x5_data);
    x6_lbl = gtk_label_new("X6: ");
    x6_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x6_data);
    x7_lbl = gtk_label_new("X7: ");
    x7_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x7_data);
    x8_lbl = gtk_label_new("X8: ");
    x8_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x8_data);
    x9_lbl = gtk_label_new("X9: ");
    x9_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x9_data);
    x10_lbl = gtk_label_new("X10: ");
    x10_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x10_data);
    x11_lbl = gtk_label_new("X11: ");
    x11_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x11_data);
    x12_lbl = gtk_label_new("X12: ");
    x12_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x12_data);
    x13_lbl = gtk_label_new("X13: ");
    x13_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x13_data);
    x14_lbl = gtk_label_new("X14: ");
    x14_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x14_data);
    x15_lbl = gtk_label_new("X15: ");
    x15_data = gtk_label_new("none");
    data_box_list = g_list_append(data_box_list, x15_data);
    space = gtk_label_new(NULL);


    gtk_grid_attach(GTK_GRID(inst_grid), inst_lbl, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(inst_grid), inst_data, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(inst_grid), cmd_lbl, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(inst_grid), cmd_data, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(inst_grid), dest_lbl, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(inst_grid), dest_data, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(inst_grid), src1_lbl, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(inst_grid), src1_data, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(inst_grid), src2_lbl, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(inst_grid), src2_data, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(inst_grid), val_lbl, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(inst_grid), val_data, 1, 5, 1, 1);

    gtk_grid_attach(GTK_GRID(mem_grid), pc_lbl, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), pc_data, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x1_lbl, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x1_data, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x2_lbl, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x2_data, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x3_lbl, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x3_data, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x4_lbl, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x4_data, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x5_lbl, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x5_data, 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x6_lbl, 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x6_data, 1, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x7_lbl, 0, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x7_data, 1, 7, 1, 1);

    gtk_grid_attach(GTK_GRID(mem_grid), space, 2, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(mem_grid), x8_lbl, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x8_data, 4, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x9_lbl, 3, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x9_data, 4, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x10_lbl, 3, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x10_data, 4, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x11_lbl, 3, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x11_data, 4, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x12_lbl, 3, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x12_data, 4, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x13_lbl, 3, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x13_data, 4, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x14_lbl, 3, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x14_data, 4, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x15_lbl, 3, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(mem_grid), x15_data, 4, 7, 1, 1);

    gtk_widget_set_halign(val_lbl, GTK_ALIGN_END);
    gtk_widget_set_halign(src1_lbl, GTK_ALIGN_END);
    gtk_widget_set_halign(src2_lbl, GTK_ALIGN_END);
    gtk_widget_set_halign(x8_lbl, GTK_ALIGN_END);
    gtk_widget_set_halign(x9_lbl, GTK_ALIGN_END);

    /****************************************************************
     *                  GESTION DES SIGNAUX
     ****************************************************************/
    //signal pour la selection du fichier
    g_signal_connect_swapped(dialog_btn, "clicked",
                             G_CALLBACK(on_file_selection),
                             window);

    //signal pour les 3 modes possibles
    g_signal_connect(GTK_TOGGLE_BUTTON(mode_c), "toggled",
                     G_CALLBACK(on_mode_selection), window);
    g_signal_connect(GTK_TOGGLE_BUTTON(mode_p), "toggled",
                     G_CALLBACK(on_mode_selection), window);
    g_signal_connect(GTK_TOGGLE_BUTTON(mode_d), "toggled",
                     G_CALLBACK(on_mode_selection), window);

    //signal pour le boutton de démarrage
    g_signal_connect_swapped (start_btn, "clicked",
                              G_CALLBACK(on_start),
                              window);

    //signal pour le boutton de démarrage
    g_signal_connect_swapped (stop_btn, "clicked",
                              G_CALLBACK(on_stop),
                              window);

    //signal pour le boutton de fermeture
    g_signal_connect_swapped (close_btn, "clicked",
                              G_CALLBACK(on_close),
                              app);

    //pour le boutton de reset
    g_signal_connect_swapped (reset_btn, "clicked",
                              G_CALLBACK(on_reset),
                              window);

    //pour le boutton de next
    g_signal_connect_swapped (next_btn, "clicked",
                              G_CALLBACK(next_clicked),
                              window);

    //pour le boutton de précédent
    g_signal_connect_swapped (prev_btn, "clicked",
                              G_CALLBACK(prev_clicked),
                              window);

    //pour le boutton de debug
    g_signal_connect_swapped (debug_btn, "clicked",
                              G_CALLBACK(debug_clicked),
                              window);


    //état initial
    on_reset();
    //affichage de tous les widget
    gtk_widget_show_all(window);
    //les widgets initialement cachés
    gtk_widget_hide(hbox_debug);
    gtk_widget_hide(hbox_next_prev_btn);
}


void update_les_label_registre()
{
    int32_t val;
    char hex[11];
    int i = 0;
    GList *l;
    for (l = g_list_nth(data_box_list, 6); l != NULL; l = l->next)
    {
        val = processeur->registres[i];
        sprintf(hex, "0x%08x", val);

        gtk_label_set_text(l->data, hex);

        i++;
    }
}


void execute_instruction()
{
    char hex[11];

    instruction = processeur->instructions[(int) (processeur->pc)];

    l = g_list_nth(data_box_list, 0);
    sprintf(hex, "0x%s", instruction.code_hexa);
    gtk_label_set_text(l->data, hex);
    l = g_list_nth(data_box_list, 1);
    gtk_label_set_text(l->data, instruction.nom);
    l = g_list_nth(data_box_list, 2);
    sprintf(hex, "0x%x", instruction.registre_destination);
    gtk_label_set_text(l->data, hex);
    l = g_list_nth(data_box_list, 3);
    sprintf(hex, "0x%x", instruction.registre_source1);
    gtk_label_set_text(l->data, hex);
    l = g_list_nth(data_box_list, 4);
    sprintf(hex, "0x%x", instruction.registre_source2);
    gtk_label_set_text(l->data, hex);
    //mise à jour du immediat
    l = g_list_nth(data_box_list, 5);
    sprintf(hex, "0x%x", instruction.immediat);
    gtk_label_set_text(l->data, hex);
    //mise à jour du label data pc
    l = g_list_nth(data_box_list, 6);
    sprintf(hex, "0x%x", processeur->pc);
    gtk_label_set_text(l->data, hex);;

    if (strcmp(instruction.nom, "LB") == 0)
    {
        load_byte(&instruction, processeur->registres, processeur->memoire);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "LH") == 0)
    {
        load_halfword(&instruction, processeur->registres, processeur->memoire);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "LW") == 0)
    {
        load_word(&instruction, processeur->registres, processeur->memoire);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "LBU") == 0)
    {
        load_byte_unsigned(&instruction, processeur->registres,
                           processeur->memoire);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "LHU") == 0)
    {
        load_halfword_unsigned(&instruction, processeur->registres,
                               processeur->memoire);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SB") == 0)
    {
        store_byte(&instruction, processeur->registres, processeur->memoire);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SH") == 0)
    {
        store_half_word(&instruction, processeur->registres,
                        processeur->memoire);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SW") == 0)
    {
        store_word(&instruction, processeur->registres, processeur->memoire);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SLL") == 0)
    {
        shift_left(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SLLI") == 0)
    {
        shift_left_immediate(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SRL") == 0)
    {
        shift_right(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SRLI") == 0)
    {
        shift_right_immediate(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SRA") == 0)
    {
        shift_right_arith(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SRAI") == 0)
    {
        shift_right_arith_immediate(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "ADD") == 0)
    {
        addition(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "ADDI") == 0)
    {
        addition_immediate(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SUB") == 0)
    {
        subtract(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "LUI") == 0)
    {
        load_upper_immediate(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "AUIPC") == 0)
    {
        add_upper_imm_to_pc(&instruction, processeur->registres,
                            &processeur->pc);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "XOR") == 0)
    {
        xor(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "XORI") == 0)
    {
        xor_immediate(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "OR") == 0)
    {
        or(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "ORI") == 0)
    {
        or_immediate(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "AND") == 0)
    {
        and(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "ANDI") == 0)
    {
        and_immediate(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SLT") == 0)
    {
        set(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SLTI") == 0)
    {
        set_immediate(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SLTU") == 0)
    {
        set_unsigned(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "SLTIU") == 0)
    {
        set_immediate_unsigned(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "BEQ") == 0)
    {
        branch_equal(&instruction, processeur->registres, &processeur->pc);
    }
    else if (strcmp(instruction.nom, "BNE") == 0)
    {
        branch_not_equal(&instruction, processeur->registres, &processeur->pc);
    }
    else if (strcmp(instruction.nom, "BLT") == 0)
    {
        branch_less_than(&instruction, processeur->registres, &processeur->pc);
    }
    else if (strcmp(instruction.nom, "BGE") == 0)
    {
        branch_greater_or_equal(&instruction, processeur->registres,
                                &processeur->pc);
    }
    else if (strcmp(instruction.nom, "BLTU") == 0)
    {
        branch_less_unsigned(&instruction, processeur->registres,
                             &processeur->pc);
    }
    else if (strcmp(instruction.nom, "BGEU") == 0)
    {
        branch_greater_or_equal_unsigned(&instruction, processeur->registres,
                                         &processeur->pc);
    }
    else if (strcmp(instruction.nom, "JAL") == 0)
    {
        jump_and_link(&instruction, processeur->registres, &processeur->pc);
    }
    else if (strcmp(instruction.nom, "JALR") == 0)
    {
        jump_and_link_register(&instruction, processeur->registres,
                               &processeur->pc);
    }
    else if (strcmp(instruction.nom, "MUL") == 0)
    {
        multiply(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "MULH") == 0)
    {
        multiply_high(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "MULHSU") == 0)
    {
        multiply_high_unsigned_signed(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "MULHU") == 0)
    {
        multiply_high_unsigned(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "DIV") == 0)
    {
        divide(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "DIVU") == 0)
    {
        divide_unsigned(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "REM") == 0)
    {
        remainder_p(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }
    else if (strcmp(instruction.nom, "REMU") == 0)
    {
        remainder_unsigned(&instruction, processeur->registres);
        processeur->pc = processeur->pc + 1;
    }

    //mise à jour des labels de chaque registre
    update_les_label_registre();

    g_main_context_iteration(NULL, FALSE);

    processeur->nb_instructions_executees++;

    printf("nom: %s \n", instruction.nom);
}