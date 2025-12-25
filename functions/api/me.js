export async function onRequestGet({ request }) {
  const cookie = request.headers.get("Cookie") || "";
  const m = cookie.match(/(?:^|;\s*)user=([^;]+)/);
  if (!m) return new Response("Not logged in", { status: 401 });

  const username = decodeURIComponent(m[1]);
  return Response.json({ username });
}
