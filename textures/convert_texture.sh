#!/bin/bash

# Nombre de couleurs max (idéal pour la MinilibX)
COLORS=256

echo "🚀 Début de la conversion des textures..."

# On boucle sur les extensions jpg, jpeg et png (insensible à la casse)
for img in *.[jJ][pP][gG] *.[jJ][pP][eE][gG] *.[pP][nN][gG]; do
    
    # Vérifier si le fichier existe (évite les erreurs si une extension manque)
    [ -e "$img" ] || continue

    # Définir le nom de sortie (on remplace l'extension par .xpm)
    output="${img%.*}.xpm"

    echo "Converting: $img -> $output"

    # Conversion avec limitation de palette et suppression des profils inutiles
    magick "$img" -colors $COLORS +profile "*" "$output"

done

echo "✅ Conversion terminée !"
