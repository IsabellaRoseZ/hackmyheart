export async function onRequestPost({ request, env }) {
  const form = await request.formData();
  const challenge = String(form.get("challenge") || "").trim(); // e.g. "01"
  const flag = String(form.get("flag") || "").trim();

  const correct = env[`FLAG_${challenge}`]; // FLAG_01, FLAG_02, ...
  if (!correct) return new Response("Invalid challenge.", { status: 400 });

  return new Response(flag === correct ? "✅ Correct!" : "❌ Incorrect.");
}
