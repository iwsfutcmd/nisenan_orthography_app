<script lang="ts">
    import { slide } from "svelte/transition";
  
    const baseWords: string[] = [
      "Nišenaan",
      "bysep’yyk’",
      "cëëwmukum",
      `"Nik myymaadi de sawisma!" 
  "Otanbodi de sawisma!"
  "Nik myymaadi de sawisma!"
  "Otanbodi de sawisma!"`,
      `K’ut’im pitcaak’am ham lajim peenim haj uk’ojmukum jamanna pittaatak’a pak’oji. Han haj k’ut’im pitcaak’am ba toojeen myji pamukum. Hace haj k’ut’im pitcaak’ak ba cëëwmukum. Hace haj pitcaak’am woomukum. Han haj woon ek’ojusan emukum sa tajim k’awna. Han haj 
  "Nik myymaadi de sawisma!" 
  "Otanbodi de sawisma!"
  "Nik myymaadi de sawisma!"
  "Otanbodi de sawisma!"
  Hace haj "Hode? Hode?" hamukum. "Hode mym sam?" "Myym da hodo taji sa." K’ut’im myjna etan emukum sa. Han haj kaanteem wak’a heet’amukum. Hace haj kaanteem wak’am uk’ojsyn k’aamukum sa meek’ojsyn. Han haj kapam hadykym k’utonim nek kyymukum. Hace haj lismo s woojok’ojmukum. Hace haj lisnom uk’ojin mym sa loomukum. Han haj toojeemukum. Han haj dappe emukum. Hace haj dappem "homaa be, ty?" han "Aj, nik’i paanim my!" hamukum. "Maat’im!" hamukum. "Oo, mej nik, ty!" "Pa macak’ii ni!" "Ok’om dani!" "Oo, nik’i pajjom hesupajim my!" "Oo, mej nik, ty!" "Myji dani aanik’i!" Hace haj "Oo, sam my!" "Oo, mej nik, ty!" "Mym sa dani aanik’i!" Han haj... umm... he got mad... Han haj mym sani wo’opajmukum. Hace haj hedem k’awim samukum. Dappem t’aanon woonomukum`,
    ];
  
    let customText = "Nisenaan";
  
    let noCaps = false;
  
    type OrthographyOption = [
      Array<string | RegExp>,
      { [key: string]: Array<string> }
    ];
  
    // prettier-ignore
    const orthographyOptions: {[key: string]: OrthographyOption} = {
      "p’": [["p’", "P’"], {
        "ṕ": ["ṕ", "Ṕ"],
        "ᵽ": ["ᵽ", "Ᵽ"],
        "ƥ": ["ƥ", "Ƥ"],
        "ṗ": ["ṗ", "Ṗ"],
  
      }],
      "t’": [["t’", "T’"], {
        "t́": ["t́", "T́"],
        "ŧ": ["ŧ", "Ŧ"],
        "ƭ": ["ƭ", "Ƭ"],
        "ṭ": ["ṭ", "Ṭ"],
        "ʇ": ["ʇ", "Ʇ"]
      }],
      "k’": [["k’", "K’"], {
        "ḱ": ["ḱ", "Ḱ"],
        "ꝁ": ["ꝁ", "Ꝁ"],
        "ƙ": ["ƙ", "Ƙ"],
        "ḳ": ["ḳ", "Ḳ"],
        "ʞ": ["ʞ", "Ʞ"],
      }],
      "c": [["c", "C"], {
        "ts": ["ts", "Ts"]
      }],
      "c’": [["c’", "C’"], {
        "ć": ["ć", "Ć"],
        "ꞓ": ["ꞓ", "Ꞓ"],
        "ƈ": ["ƈ", "Ƈ"],
        "c̣": ["c̣", "C̣"],
        "ts’": ["ts’", "Ts’"]
      }],
      "y": [["y", "Y"], {
        "ʉ": ["ʉ", "Ʉ"],
        "ɨ": ["ɨ", "Ɨ"]
      }],
      "b": [["b", "B"], {
        "ƀ": ["ƀ", "Ƀ"],
        "ɓ": ["ɓ", "Ɓ"],
      }],
      "d": [["d", "D"], {
        "đ": ["đ", "Đ"],
        "ɗ": ["ɗ", "Ɗ"],
      }],
      "j": [["j", "J"], {
        "y": ["y", "Y"]
      }],
      "ë": [["ë", "Ë"], {
        "ə": ["ə", "Ə"]
      }],
      "’": [[/(?<![ptkPTK])’/g], {
        "ʔ": ["ʔ"]
      }],
      "aa": [[/([aeiouyë]){2}/ig], {
        "aː": ["$1ː"]
      }],
      "š": [["š", "Š"], {
        "sh": ["sh", "Sh"],
        "ś": ["ś", "Ś"],
        "ş": ["ş", "Ş"],
        "ŝ": ["ŝ", "Ŝ"],
        "ꟊ": ["ꟊ", "Ꟊ"],
        "ꞩ": ["ꞩ", "Ꞩ"],
      }]
    };
  
    const keyOrder = [
      "aa",
      "’",
      "p’",
      "t’",
      "k’",
      "c",
      "c’",
      "b",
      "d",
      "š",
      "j",
      "ë",
      "y",
    ];
  
    const keyDiff = keyOrder.filter(
      (x) => !Object.keys(orthographyOptions).includes(x)
    );
    const keyDiff2 = Object.keys(orthographyOptions).filter(
      (x) => !keyOrder.includes(x)
    );
    console.assert(
      keyDiff2.length === 0 && keyDiff.length === 0,
      keyDiff,
      keyDiff2
    );
  
    const complexKeys = ["p’", "t’", "k’", "c’", "š", "ë", "’"];
  
    const fonts = [
      "Noto Sans",
      "Noto Serif",
      "Noto Sans Display",
      "Noto Serif Display",
      "Arial",
      "Times New Roman",
    ];
  
    const fontDefaults = {
      size: 12,
      weight: 400,
      width: 100,
      contrast: 0,
      italic: false,
      underline: false,
      smallCaps: false,
    };
    let fontSize: number;
    let fontWeight: number;
    let fontWidth: number;
    let fontContrast: number;
    let fontItalic: boolean;
    let fontUnderline: boolean;
    let fontSmallCaps: boolean;
  
    const resetFontOptions = () => {
      fontSize = fontDefaults.size;
      fontWeight = fontDefaults.weight;
      fontWidth = fontDefaults.width;
      fontContrast = fontDefaults.contrast;
      fontItalic = fontDefaults.italic;
      fontUnderline = fontDefaults.underline;
      fontSmallCaps = fontDefaults.smallCaps;
    };
    resetFontOptions();
    let currentOrthography: Array<[string, string]> = keyOrder.map((key) => [
      key,
      null,
    ]);
  
    const transliterate = (
      baseWords: string[],
      currentOrthography: Array<[string, string]>,
      noCaps: boolean
    ) =>
      baseWords.map((baseWord) => {
        [...currentOrthography].forEach(([inputKey, outputKey]) => {
          if (outputKey) {
            const inputs = orthographyOptions[inputKey][0];
            const outputs = orthographyOptions[inputKey][1][outputKey];
            inputs.forEach((input, i) => {
              baseWord = baseWord.replaceAll(input, outputs[i]);
            });
          }
        });
        return noCaps ? baseWord.toLowerCase() : baseWord;
      });
  
    let result: string[] = [];
  
    let menusOpen: string[] = [];
  
    const toggleMenu = (option: string) => {
      menusOpen = menusOpen.includes(option) ? [] : [option];
    };
  
    let shiftPressed = false;
  
    $: {
      result = transliterate(
        [customText, ...baseWords],
        currentOrthography,
        noCaps
      );
    }
  </script>
  
  <svelte:window
    on:keydown={(e) => {
      if (e.key === "Shift") shiftPressed = true;
    }}
    on:keyup={(e) => {
      if (e.key === "Shift") shiftPressed = false;
    }}
  />
  
  <main>
    <div id="options-bar">
      <div id="options-buttons">
        <button on:click={() => toggleMenu("orthography")}>
          Orthography Options
        </button>
        <button on:click={() => toggleMenu("customText")}> Custom Text </button>
        <button on:click={() => toggleMenu("font")}> Font Options </button>
      </div>
      {#if menusOpen.includes("orthography")}
        <div transition:slide class="options">
          {#each keyOrder as inputKey, i}
            <form class="orthography-option">
              <input
                type="radio"
                bind:group={currentOrthography[i][1]}
                name={inputKey}
                id={inputKey + "-" + inputKey}
                value={null}
                checked
              />
              <label for={inputKey + "-" + inputKey}>{inputKey}</label>
              {#each Object.keys(orthographyOptions[inputKey][1]) as outputKey}
                <input
                  type="radio"
                  bind:group={currentOrthography[i][1]}
                  name={inputKey}
                  id={inputKey + "-" + outputKey}
                  value={outputKey}
                />
                <label for={inputKey + "-" + outputKey}>{outputKey}</label>
              {/each}
            </form>
          {/each}
          <form class="orthography-option">
            <input
              type="checkbox"
              bind:checked={noCaps}
              name="all-caps"
              id="all-caps"
            />
            <label for="all-caps">{noCaps ? "abc" : "Abc"}</label>
          </form>
        </div>
      {/if}
      {#if menusOpen.includes("customText")}
        <div transition:slide id="custom-text">
          <textarea id="custom-text-area" bind:value={customText} />
          <div>
            {#each complexKeys as key}
              <button
                on:click={() => {
                  customText =
                    customText + (shiftPressed ? key.toUpperCase() : key);
                  document.getElementById("custom-text-area").focus();
                }}
              >
                {shiftPressed ? key.toUpperCase() : key}
              </button>
            {/each}
          </div>
        </div>
      {/if}
      {#if menusOpen.includes("font")}
        <div transition:slide class="options" id="font-options">
          <form class="font-options">
            <label>
              Font Size: {fontSize}
              <input type="range" bind:value={fontSize} />
            </label>
            <label>
              Font Weight: {fontWeight}
              <input type="range" bind:value={fontWeight} min="100" max="900" />
            </label>
            <label>
              Font Width: {fontWidth}
              <input
                type="range"
                bind:value={fontWidth}
                min="62.5"
                max="100"
                step="0.5"
              />
            </label>
            <label>
              Font Contrast: {fontContrast}
              <input type="range" bind:value={fontContrast} min="0" max="100" />
            </label>
            <label style="flex-direction: row;">
              <input type="checkbox" bind:checked={fontItalic} />
              Italic
            </label>
            <label style="flex-direction: row;">
              <input type="checkbox" bind:checked={fontUnderline} />
              Underline
            </label>
            <label style="flex-direction: row;">
              <input type="checkbox" bind:checked={fontSmallCaps} />
              Small Caps
            </label>
          </form>
          <button on:click={resetFontOptions}>Reset</button>
        </div>
      {/if}
    </div>
    <div id="output" on:click={() => (menusOpen = [])}>
      {#each fonts as font}
        <details class="results" style:font-family="'{font}', 'Last Resort'" open>
          <summary>{font}</summary>
          <div
            style:font-size="{fontSize}pt"
            style:font-variation-settings="'wght' {fontWeight}, 'wdth' {fontWidth},
            'CTGR' {fontContrast}"
            style:font-style={fontItalic ? "italic" : ""}
            style:text-decoration={fontUnderline ? "underline" : ""}
            style:font-variant={fontSmallCaps ? "small-caps" : ""}
          >
            {#each result as output}
              {output}
              <hr />
            {/each}
          </div>
        </details>
      {/each}
    </div>
  </main>
  
  <style>
    @import url("https://fonts.cdnfonts.com/css/times-new-roman");
    @import url("https://fonts.cdnfonts.com/css/arial");
  
    @font-face {
      font-family: "Last Resort";
      src: url("/fonts/LastResortHE-Regular.ttf") format("truetype");
    }
    @font-face {
      font-family: "Noto Sans";
      src: url("/fonts/NotoSans-VF.ttf") format("truetype-variations");
    }
    @font-face {
      font-family: "Noto Serif";
      src: url("/fonts/NotoSerif-VF.ttf") format("truetype-variations");
    }
    @font-face {
      font-family: "Noto Sans Display";
      src: url("/fonts/NotoSansDisplay-VF.ttf") format("truetype-variations");
    }
    @font-face {
      font-family: "Noto Serif Display";
      src: url("/fonts/NotoSerifDisplay-VF.ttf") format("truetype-variations");
    }
    @font-face {
      font-family: "Noto Sans";
      src: url("/fonts/NotoSans-Italic-VF.ttf") format("truetype-variations");
      font-style: italic;
    }
    @font-face {
      font-family: "Noto Serif";
      src: url("/fonts/NotoSerif-Italic-VF.ttf") format("truetype-variations");
      font-style: italic;
    }
    @font-face {
      font-family: "Noto Sans Display";
      src: url("/fonts/NotoSansDisplay-Italic-VF.ttf")
        format("truetype-variations");
      font-style: italic;
    }
    @font-face {
      font-family: "Noto Serif Display";
      src: url("/fonts/NotoSerifDisplay-Italic-VF.ttf")
        format("truetype-variations");
      font-style: italic;
    }
  
    :root {
      font-family: "Noto Sans";
    }
  
    main {
      display: flex;
      flex-direction: column;
    }
  
    #options-bar {
      position: sticky;
      inset-block-start: 8px;
    }
    #options-buttons {
      display: flex;
      flex-direction: row;
      justify-content: space-between;
    }
  
    .options {
      position: relative;
      background-color: white;
      display: flex;
      flex-direction: column;
      border: 1px black solid;
      padding: 8px;
    }
  
    #custom-text {
      position: relative;
      display: flex;
      inline-size: auto;
      flex-direction: column;
      align-items: center;
    }
  
    #custom-text > textarea {
      inline-size: 100%;
    }
    /* #font-options {
      inset-inline-end: 8px;
    } */
    .options > form {
      display: flex;
    }
  
    .options > form.orthography-option {
      flex-direction: row;
      border-block-end: 1px black solid;
      font-size: 18pt;
    }
  
    .options > form.font-options {
      flex-direction: column;
    }
  
    .options > form.font-options > label {
      display: flex;
      flex-direction: column;
    }
  
    input[type="radio"] {
      appearance: none;
      margin: 0;
      block-size: 0px;
      inline-size: 0px;
    }
  
    input[type="radio"] + label {
      text-align: center;
      min-inline-size: 24px;
      border-radius: 4pt;
    }
    input[type="radio"]:checked + * {
      background-color: lightblue;
    }
    #output {
      overflow: scroll;
    }
    .results {
      white-space: pre-wrap;
      margin-inline-start: 8px;
      inline-size: fit-content;
    }
  </style>
  